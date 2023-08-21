#include "Renderer.h"

using namespace DirectX;
using namespace SimpleMath;
using Microsoft::WRL::ComPtr;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Initialise(IDXGISwapChain* pSwapChain, ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
    this->hwnd = hwnd;
    this->m_swapChain = pSwapChain;
    this->m_device = pDevice;
    this->m_deviceContext = pDeviceContext;
    this->m_height = 1080;
    this->m_width = 1920;

    this->CreateResources();
}

void Renderer::CreateResources()
{
    // Clear the previous window size specific context.
    this->m_deviceContext->OMSetRenderTargets(0, nullptr, nullptr);
    m_deviceContext->Flush();

    const UINT backBufferWidth = static_cast<UINT>(this->m_width);
    const UINT backBufferHeight = static_cast<UINT>(this->m_height);
    const DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
    const DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    constexpr UINT backBufferCount = 2;

    HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

    // Obtain the backbuffer for this window which will be the final 3D rendertarget.
    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

    // Create a view interface on the rendertarget to use on bind.
    DX::ThrowIfFailed(this->m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, &this->m_renderTargetViewViewport));

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

    m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(this->m_deviceContext);
}

void Renderer::Render()
{
    this->m_deviceContext->ClearRenderTargetView(m_renderTargetViewViewport, Colors::CornflowerBlue);
    this->m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.f);

    this->m_deviceContext->OMSetRenderTargets(1, &m_renderTargetViewViewport, m_depthStencilView);

    if (m_renderTargetViewViewport)
    {
        this->m_deviceContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
        this->m_deviceContext->OMSetDepthStencilState(m_states->DepthNone(), 0);
        this->m_deviceContext->RSSetState(m_states->CullNone());

        m_effect->Apply(this->m_deviceContext);

        this->m_deviceContext->IASetInputLayout(m_inputLayout.Get());

        m_batch->Begin();

        VertexPositionColor v1(Vector3(0.f, 0.5f, 0.5f), Colors::Yellow);
        VertexPositionColor v2(Vector3(0.5f, -0.5f, 0.5f), Colors::Yellow);
        VertexPositionColor v3(Vector3(-0.5f, -0.5f, 0.5f), Colors::Yellow);

        m_batch->DrawTriangle(v1, v2, v3);

        m_batch->End();
    }
}

void Renderer::HandleResize(int width, int height)
{
    this->m_renderTargetTextureViewport->Release();
    this->m_renderTargetTextureViewport = nullptr;

    this->m_renderTargetViewViewport->Release();
    this->m_renderTargetViewViewport = nullptr;

    this->m_shaderResourceViewViewport->Release();
    this->m_shaderResourceViewViewport = nullptr;

    this->m_height = (std::max)(height, 1);
    this->m_width = (std::max)(width, 1);

    this->CreateResources();
}