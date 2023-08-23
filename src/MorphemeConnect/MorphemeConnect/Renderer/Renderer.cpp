#include "Renderer.h"
#include "StepTimer.h"

using namespace DirectX;
using namespace SimpleMath;
using Microsoft::WRL::ComPtr;

namespace
{
    constexpr UINT MSAA_COUNT = 4;
    constexpr UINT MSAA_QUALITY = 0;
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Initialise(HWND hwnd, IDXGISwapChain* pSwapChain, ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext, ID3D11RenderTargetView* pRenderTargetView)
{
    this->m_window = hwnd;
    this->m_swapChain = pSwapChain;
    this->m_device = pDevice;
    this->m_deviceContext = pDeviceContext;
    this->m_renderTargetViewViewport = pRenderTargetView;
    this->m_height = 1280;
    this->m_width = 800;
    this->m_viewportWidth = 1200;
    this->m_viewportHeight = 800;

    this->CreateResources();
}

void Renderer::CreateResources()
{
    // Clear the previous window size specific context.
    const UINT backBufferWidth = static_cast<UINT>(this->m_width);
    const UINT backBufferHeight = static_cast<UINT>(this->m_height);
    const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_UNKNOWN;
    const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    constexpr UINT backBufferCount = 0;

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.

    // Allocate a 2-D surface as the depth/stencil buffer and
    // create a DepthStencil view on this surface to use on bind.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

    ComPtr<ID3D11Texture2D> depthStencil;
    DX::ThrowIfFailed(this->m_device->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

    DX::ThrowIfFailed(this->m_device->CreateDepthStencilView(depthStencil.Get(), nullptr, &this->m_depthStencilView));

    D3D11_TEXTURE2D_DESC textureDesc;
    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

    ///////////////////////// Map's Texture
    // Initialize the  texture description.
    ZeroMemory(&textureDesc, sizeof(textureDesc));

    // Setup the texture description.
    // We will have our map be a square
    // We will need to have this texture bound as a render target AND a shader resource
    textureDesc.Width = m_width;
    textureDesc.Height = m_height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

    // Create the texture
    m_device->CreateTexture2D(&textureDesc, NULL, &this->m_renderTargetTextureViewport);

    /////////////////////// Map's Render Target
    // Setup the description of the render target view.
    renderTargetViewDesc.Format = textureDesc.Format;
    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDesc.Texture2D.MipSlice = 0;

    // Create the render target view.
    m_device->CreateRenderTargetView(this->m_renderTargetTextureViewport, &renderTargetViewDesc, &this->m_renderTargetViewViewport);

    /////////////////////// Map's Shader Resource View
    // Setup the description of the shader resource view.
    shaderResourceViewDesc.Format = textureDesc.Format;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;

    // Create the shader resource view.
    m_device->CreateShaderResourceView(this->m_renderTargetTextureViewport, &shaderResourceViewDesc, &this->m_shaderResourceViewViewport);

    m_states = std::make_unique<CommonStates>(this->m_device);

    m_effect = std::make_unique<BasicEffect>(this->m_device);
    m_effect->SetVertexColorEnabled(true);

    DX::ThrowIfFailed(
        CreateInputLayoutFromEffect<VertexPositionColor>(this->m_device, m_effect.get(),
            m_inputLayout.ReleaseAndGetAddressOf())
    );

    m_fxFactory = std::make_unique<EffectFactory>(this->m_device);

    //m_model = Model::CreateFromCMO(this->m_device, L"cup.cmo", *m_fxFactory);

    m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(this->m_deviceContext);

    m_view = Matrix::CreateLookAt(Vector3(2.f, 2.f, 2.f),
        Vector3::Zero, Vector3::UnitY);
    m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
        float(this->m_width) / float(this->m_height), 0.1f, 10.f);
    m_world = Matrix::Identity;

    m_effect->SetView(m_view);
    m_effect->SetProjection(m_proj);
    m_effect->SetWorld(m_world);

    CD3D11_RASTERIZER_DESC rastDesc(D3D11_FILL_SOLID, D3D11_CULL_NONE, FALSE,
        D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
        D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, TRUE, FALSE);

    auto device = this->m_device;
    auto width = this->m_width;
    auto height = this->m_height;

    CD3D11_TEXTURE2D_DESC rtDesc(DXGI_FORMAT_B8G8R8A8_UNORM,
        width, height, 1, 1,
        D3D11_BIND_RENDER_TARGET, D3D11_USAGE_DEFAULT, 0,
        MSAA_COUNT, MSAA_QUALITY);

    DX::ThrowIfFailed(
        device->CreateTexture2D(&rtDesc, nullptr,
            m_offscreenRenderTarget.ReleaseAndGetAddressOf()));

    CD3D11_RENDER_TARGET_VIEW_DESC rtvDesc(D3D11_RTV_DIMENSION_TEXTURE2DMS);

    DX::ThrowIfFailed(
        device->CreateRenderTargetView(m_offscreenRenderTarget.Get(),
            &rtvDesc,
            m_offscreenRenderTargetSRV.ReleaseAndGetAddressOf()));

    CD3D11_TEXTURE2D_DESC dsDesc(DXGI_FORMAT_D32_FLOAT,
        width, height, 1, 1,
        D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT, 0,
        MSAA_COUNT, MSAA_QUALITY);

    ComPtr<ID3D11Texture2D> depthBuffer;
    DX::ThrowIfFailed(
        device->CreateTexture2D(&dsDesc, nullptr, depthBuffer.GetAddressOf()));

    CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc(D3D11_DSV_DIMENSION_TEXTURE2DMS);

    DX::ThrowIfFailed(
        device->CreateDepthStencilView(depthBuffer.Get(),
            &dsvDesc,
            m_depthStencilSRV.ReleaseAndGetAddressOf()));
}

void Renderer::Update()
{
    m_timer.Tick([&]()
    {
        float delta_time = float(m_timer.GetElapsedSeconds());

        this->m_camera.Update(this->m_viewportWidth, this->m_viewportHeight, delta_time);
    });

    this->m_world = Matrix::Identity;
    this->m_view = this->m_camera.m_view;
    this->m_proj = this->m_camera.m_proj;

    this->Render();
}

void Renderer::Clear()
{
    // Clear the views.
    float color[4] = { this->m_settings.m_backgroundColor.x, this->m_settings.m_backgroundColor.y, this->m_settings.m_backgroundColor.z, this->m_settings.m_backgroundColor.w };
    this->m_deviceContext->ClearRenderTargetView(this->m_renderTargetViewViewport, color);
    this->m_deviceContext->ClearDepthStencilView(this->m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    this->m_deviceContext->OMSetRenderTargets(1, &this->m_renderTargetViewViewport, this->m_depthStencilView);

    // Set the viewport.
    D3D11_VIEWPORT viewport = { 0.0f, 0.0f, static_cast<float>(this->m_width), static_cast<float>(this->m_height), 0.f, 1.f };
    this->m_deviceContext->RSSetViewports(1, &viewport);
}

void Renderer::Render()
{
    if (this->m_timer.GetFrameCount() == 0)
        return;

    this->Clear();

    if (m_renderTargetViewViewport)
    {
        ID3D11DeviceContext* context = this->m_deviceContext;

        context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
        context->OMSetDepthStencilState(m_states->DepthNone(), 0);
        context->RSSetState(m_states->CullNone());

        m_effect->SetWorld(m_world);
        m_effect->SetView(m_view);
        m_effect->SetProjection(m_proj);
        m_effect->Apply(context);

        context->IASetInputLayout(m_inputLayout.Get());

        m_batch->Begin();

        DX::DrawGrid(this->m_batch.get(), this->m_settings.m_gridScale * Vector3::UnitX, this->m_settings.m_gridScale * Vector3::UnitZ, this->m_camera.m_targetPos, 100, 100, Colors::White);
        
        DX::DrawOriginMarker(this->m_batch.get(), XMMatrixTranslationFromVector(Vector3::Zero), 0.5f, Colors::DarkCyan);
              
        m_batch->End();

        context->ResolveSubresource(this->m_renderTargetTextureViewport, 0,
            m_offscreenRenderTarget.Get(), 0,
            DXGI_FORMAT_B8G8R8A8_UNORM);
    }
}

void Renderer::SetRenderResolution(int width, int height)
{
    this->m_height = (std::max)(height, 1);
    this->m_width = (std::max)(width, 1);
}

void Renderer::SetViewportSize(int width, int height)
{
    this->m_viewportWidth = (std::max)(height, 1);
    this->m_viewportHeight = (std::max)(width, 1);
}