//--------------------------------------------------------------------------------------
// File: DebugDraw.cpp
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//-------------------------------------------------------------------------------------
#include "DebugDraw.h"
#include "Renderer.h"

#include <algorithm>

using namespace DirectX;
using namespace DirectX::SimpleMath;

namespace
{
    inline void XM_CALLCONV DrawCube(PrimitiveBatch<VertexPositionColor>* batch,
        CXMMATRIX matWorld,
        FXMVECTOR color)
    {
        static const XMVECTORF32 s_verts[8] =
        {
            { { { -1.f, -1.f, -1.f, 0.f } } },
            { { {  1.f, -1.f, -1.f, 0.f } } },
            { { {  1.f, -1.f,  1.f, 0.f } } },
            { { { -1.f, -1.f,  1.f, 0.f } } },
            { { { -1.f,  1.f, -1.f, 0.f } } },
            { { {  1.f,  1.f, -1.f, 0.f } } },
            { { {  1.f,  1.f,  1.f, 0.f } } },
            { { { -1.f,  1.f,  1.f, 0.f } } }
        };

        static const WORD s_indices[] =
        {
            0, 1,
            1, 2,
            2, 3,
            3, 0,
            4, 5,
            5, 6,
            6, 7,
            7, 4,
            0, 4,
            1, 5,
            2, 6,
            3, 7
        };

        VertexPositionColor verts[8];
        for (size_t i = 0; i < 8; ++i)
        {
            const XMVECTOR v = XMVector3Transform(s_verts[i], matWorld);
            XMStoreFloat3(&verts[i].position, v);
            XMStoreFloat4(&verts[i].color, color);
        }

        batch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_LINELIST, s_indices, static_cast<UINT>(std::size(s_indices)), verts, 8);
    }
}

void XM_CALLCONV DX::Draw(PrimitiveBatch<VertexPositionColor>* batch,
    const BoundingSphere& sphere,
    FXMVECTOR color)
{
    const XMVECTOR origin = XMLoadFloat3(&sphere.Center);

    const float radius = sphere.Radius;

    const XMVECTOR xaxis = XMVectorScale(g_XMIdentityR0, radius);
    const XMVECTOR yaxis = XMVectorScale(g_XMIdentityR1, radius);
    const XMVECTOR zaxis = XMVectorScale(g_XMIdentityR2, radius);

    DrawRing(batch, origin, xaxis, zaxis, color);
    DrawRing(batch, origin, xaxis, yaxis, color);
    DrawRing(batch, origin, yaxis, zaxis, color);
}

void XM_CALLCONV DX::Draw(PrimitiveBatch<VertexPositionColor>* batch,
    const BoundingBox& box,
    FXMVECTOR color)
{
    XMMATRIX matWorld = XMMatrixScaling(box.Extents.x, box.Extents.y, box.Extents.z);
    const XMVECTOR position = XMLoadFloat3(&box.Center);
    matWorld.r[3] = XMVectorSelect(matWorld.r[3], position, g_XMSelect1110);

    DrawCube(batch, matWorld, color);
}

void XM_CALLCONV DX::Draw(PrimitiveBatch<VertexPositionColor>* batch,
    const BoundingOrientedBox& obb,
    FXMVECTOR color)
{
    XMMATRIX matWorld = XMMatrixRotationQuaternion(XMLoadFloat4(&obb.Orientation));
    const XMMATRIX matScale = XMMatrixScaling(obb.Extents.x, obb.Extents.y, obb.Extents.z);
    matWorld = XMMatrixMultiply(matScale, matWorld);
    const XMVECTOR position = XMLoadFloat3(&obb.Center);
    matWorld.r[3] = XMVectorSelect(matWorld.r[3], position, g_XMSelect1110);

    DrawCube(batch, matWorld, color);
}

void XM_CALLCONV DX::Draw(PrimitiveBatch<VertexPositionColor>* batch,
    const BoundingFrustum& frustum,
    FXMVECTOR color)
{
    XMFLOAT3 corners[BoundingFrustum::CORNER_COUNT];
    frustum.GetCorners(corners);

    VertexPositionColor verts[24] = {};
    verts[0].position = corners[0];
    verts[1].position = corners[1];
    verts[2].position = corners[1];
    verts[3].position = corners[2];
    verts[4].position = corners[2];
    verts[5].position = corners[3];
    verts[6].position = corners[3];
    verts[7].position = corners[0];

    verts[8].position = corners[0];
    verts[9].position = corners[4];
    verts[10].position = corners[1];
    verts[11].position = corners[5];
    verts[12].position = corners[2];
    verts[13].position = corners[6];
    verts[14].position = corners[3];
    verts[15].position = corners[7];

    verts[16].position = corners[4];
    verts[17].position = corners[5];
    verts[18].position = corners[5];
    verts[19].position = corners[6];
    verts[20].position = corners[6];
    verts[21].position = corners[7];
    verts[22].position = corners[7];
    verts[23].position = corners[4];

    for (size_t j = 0; j < std::size(verts); ++j)
    {
        XMStoreFloat4(&verts[j].color, color);
    }

    batch->Draw(D3D_PRIMITIVE_TOPOLOGY_LINELIST, verts, static_cast<UINT>(std::size(verts)));
}

void XM_CALLCONV DX::DrawGrid(PrimitiveBatch<VertexPositionColor>* batch,
    FXMVECTOR xAxis,
    FXMVECTOR yAxis,
    FXMVECTOR origin,
    size_t xdivs,
    size_t ydivs,
    GXMVECTOR color)
{
    xdivs = std::max<size_t>(1, xdivs);
    ydivs = std::max<size_t>(1, ydivs);

    for (size_t i = 0; i <= xdivs; ++i)
    {
        float percent = float(i) / float(xdivs);
        percent = (percent * 2.f) - 1.f;
        XMVECTOR scale = XMVectorScale(xAxis, percent);
        scale = XMVectorAdd(scale, origin);

        const VertexPositionColor v1(XMVectorSubtract(scale, yAxis), color);
        const VertexPositionColor v2(XMVectorAdd(scale, yAxis), color);
        batch->DrawLine(v1, v2);
    }

    for (size_t i = 0; i <= ydivs; i++)
    {
        FLOAT percent = float(i) / float(ydivs);
        percent = (percent * 2.f) - 1.f;
        XMVECTOR scale = XMVectorScale(yAxis, percent);
        scale = XMVectorAdd(scale, origin);

        const VertexPositionColor v1(XMVectorSubtract(scale, xAxis), color);
        const VertexPositionColor v2(XMVectorAdd(scale, xAxis), color);
        batch->DrawLine(v1, v2);
    }
}

void XM_CALLCONV DX::DrawRing(PrimitiveBatch<VertexPositionColor>* batch,
    FXMVECTOR origin,
    FXMVECTOR majorAxis,
    FXMVECTOR minorAxis,
    GXMVECTOR color)
{
    constexpr size_t c_ringSegments = 32;

    VertexPositionColor verts[c_ringSegments + 1];

    constexpr float fAngleDelta = XM_2PI / float(c_ringSegments);
    // Instead of calling cos/sin for each segment we calculate
    // the sign of the angle delta and then incrementally calculate sin
    // and cosine from then on.
    const XMVECTOR cosDelta = XMVectorReplicate(cosf(fAngleDelta));
    const XMVECTOR sinDelta = XMVectorReplicate(sinf(fAngleDelta));
    XMVECTOR incrementalSin = XMVectorZero();
    static const XMVECTORF32 s_initialCos =
    {
        { { 1.f, 1.f, 1.f, 1.f } }
    };
    XMVECTOR incrementalCos = s_initialCos.v;
    for (size_t i = 0; i < c_ringSegments; i++)
    {
        XMVECTOR pos = XMVectorMultiplyAdd(majorAxis, incrementalCos, origin);
        pos = XMVectorMultiplyAdd(minorAxis, incrementalSin, pos);
        XMStoreFloat3(&verts[i].position, pos);
        XMStoreFloat4(&verts[i].color, color);
        // Standard formula to rotate a vector.
        const XMVECTOR newCos = XMVectorSubtract(XMVectorMultiply(incrementalCos, cosDelta), XMVectorMultiply(incrementalSin, sinDelta));
        const XMVECTOR newSin = XMVectorAdd(XMVectorMultiply(incrementalCos, sinDelta), XMVectorMultiply(incrementalSin, cosDelta));
        incrementalCos = newCos;
        incrementalSin = newSin;
    }
    verts[c_ringSegments] = verts[0];

    batch->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, verts, c_ringSegments + 1);
}

void XM_CALLCONV DX::DrawRay(PrimitiveBatch<VertexPositionColor>* batch,
    FXMVECTOR origin,
    FXMVECTOR direction,
    bool normalize,
    FXMVECTOR color)
{
    VertexPositionColor verts[3];
    XMStoreFloat3(&verts[0].position, origin);

    XMVECTOR normDirection = XMVector3Normalize(direction);
    XMVECTOR rayDirection = (normalize) ? normDirection : direction;

    XMVECTOR perpVector = XMVector3Cross(normDirection, g_XMIdentityR1);

    if (XMVector3Equal(XMVector3LengthSq(perpVector), g_XMZero))
    {
        perpVector = XMVector3Cross(normDirection, g_XMIdentityR2);
    }
    perpVector = XMVector3Normalize(perpVector);

    XMStoreFloat3(&verts[1].position, XMVectorAdd(rayDirection, origin));
    perpVector = XMVectorScale(perpVector, 0.0625f);
    normDirection = XMVectorScale(normDirection, -0.25f);
    rayDirection = XMVectorAdd(perpVector, rayDirection);
    rayDirection = XMVectorAdd(normDirection, rayDirection);
    XMStoreFloat3(&verts[2].position, XMVectorAdd(rayDirection, origin));

    XMStoreFloat4(&verts[0].color, color);
    XMStoreFloat4(&verts[1].color, color);
    XMStoreFloat4(&verts[2].color, color);

    batch->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, verts, 2);
}

void XM_CALLCONV DX::DrawTriangle(PrimitiveBatch<VertexPositionColor>* batch,
    FXMVECTOR pointA,
    FXMVECTOR pointB,
    FXMVECTOR pointC,
    GXMVECTOR color)
{
    VertexPositionColor verts[4];
    XMStoreFloat3(&verts[0].position, pointA);
    XMStoreFloat3(&verts[1].position, pointB);
    XMStoreFloat3(&verts[2].position, pointC);
    XMStoreFloat3(&verts[3].position, pointA);

    XMStoreFloat4(&verts[0].color, color);
    XMStoreFloat4(&verts[1].color, color);
    XMStoreFloat4(&verts[2].color, color);
    XMStoreFloat4(&verts[3].color, color);

    batch->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, verts, 4);
}

void XM_CALLCONV DX::DrawQuad(PrimitiveBatch<VertexPositionColor>* batch,
    FXMVECTOR pointA,
    FXMVECTOR pointB,
    FXMVECTOR pointC,
    GXMVECTOR pointD,
    HXMVECTOR color)
{
    VertexPositionColor verts[5];
    XMStoreFloat3(&verts[0].position, pointA);
    XMStoreFloat3(&verts[1].position, pointB);
    XMStoreFloat3(&verts[2].position, pointC);
    XMStoreFloat3(&verts[3].position, pointD);
    XMStoreFloat3(&verts[4].position, pointA);

    XMStoreFloat4(&verts[0].color, color);
    XMStoreFloat4(&verts[1].color, color);
    XMStoreFloat4(&verts[2].color, color);
    XMStoreFloat4(&verts[3].color, color);
    XMStoreFloat4(&verts[4].color, color);

    batch->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, verts, 5);
}

void XM_CALLCONV DX::DrawLine(PrimitiveBatch<VertexPositionColor>* batch,
    DirectX::SimpleMath::Vector3 pointA,
    DirectX::SimpleMath::Vector3 pointB,
    GXMVECTOR color)
{
    VertexPositionColor verts[2];
    XMStoreFloat3(&verts[0].position, pointA);
    XMStoreFloat3(&verts[1].position, pointB);

    XMStoreFloat4(&verts[0].color, color);
    XMStoreFloat4(&verts[1].color, color);

    batch->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, verts, 2);
}

void XM_CALLCONV DX::DrawCapsule(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
    DirectX::XMMATRIX* world, DirectX::SimpleMath::Vector3 pointA, DirectX::SimpleMath::Vector3 pointB, float radius,
    DirectX::GXMVECTOR color)
{
    XMFLOAT4 dst;
    XMStoreFloat4(&dst, color);

    constexpr int numSlices = SPHERE_SLICES;
    constexpr int numStacks = SPHERE_STACKS;
    constexpr int numSegments = numSlices * numStacks;
    constexpr int numVertices = (2 * (numSegments + 1)) + numSlices;
    constexpr float pi = XM_PI;

    // Calculate vertex positions for the capsule
    VertexPositionColor top_vertex;
    VertexPositionColor bot_vertex;
    VertexPositionColor top_vertices[numStacks][numSlices];
    VertexPositionColor bot_vertices[numStacks][numSlices];
    VertexPositionColor mid_vertices[numSlices];
    VertexPositionColor vertices[numVertices];
    XMVECTOR transformed_pos;

    XMMATRIX rotation = XMMatrixIdentity();
    rotation = MathHelper::GetRotationFrom2Vectors(pointB, pointA);

    Vector3 center_bot = Vector3(pointA.x, pointA.y, pointA.z);
    Vector3 center_top = Vector3(pointB.x, pointB.y, pointB.z);
    Vector3 center_mid = (pointA + pointB) / 2;

    float stackAngleStep = (pi / 2) / numStacks;
    float sliceAngleStep = (2 * pi) / numSlices;

    transformed_pos = XMLoadFloat3(&center_bot);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);

    XMStoreFloat3(&center_bot, transformed_pos);

    transformed_pos = XMLoadFloat3(&center_mid);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);

    XMStoreFloat3(&center_mid, transformed_pos);

    transformed_pos = XMLoadFloat3(&center_top);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);

    XMStoreFloat3(&center_top, transformed_pos);

    bot_vertex.position = Vector3(center_bot.x, center_bot.y - radius, center_bot.z);
    bot_vertex.color = Vector4(color);

    transformed_pos = XMLoadFloat3(&bot_vertex.position);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&bot_vertex.position, transformed_pos);

    top_vertex.position = Vector3(center_top.x, center_top.y + radius, center_top.z);
    top_vertex.color = Vector4(color);

    transformed_pos = XMLoadFloat3(&top_vertex.position);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&top_vertex.position, transformed_pos);

    int vertex_idx = 0;

    vertices[vertex_idx] = top_vertex;
    vertex_idx++;

    // Draw top hemisphere
    for (int i = 0; i < numStacks; i++)
    {
        float stackAngle = i * stackAngleStep;

        for (int j = 0; j < numSlices; j++)
        {
            float sliceAngle = j * sliceAngleStep;

            float x = radius * cosf(stackAngle) * cosf(sliceAngle);
            float y = radius * sinf(stackAngle);
            float z = radius * cosf(stackAngle) * sinf(sliceAngle);

            top_vertices[i][j].position = Vector3(x, y, z) + Vector3(center_top.x, center_top.y, center_top.z);
            top_vertices[i][j].color = dst;

            transformed_pos = XMLoadFloat3(&top_vertices[i][j].position);
            transformed_pos = XMVector3Transform(transformed_pos, rotation);
            transformed_pos = XMVector3Transform(transformed_pos, *world);

            XMStoreFloat3(&top_vertices[i][j].position, transformed_pos);

            vertices[vertex_idx] = top_vertices[i][j];
            vertex_idx++;
        }
    }

    for (int j = 0; j < numSlices; j++)
    {
        float sliceAngle = j * sliceAngleStep;

        float x = radius * cosf(sliceAngle);
        float y = 0;
        float z = radius * sinf(sliceAngle);

        mid_vertices[j].position = Vector3(x, y, z) + Vector3(center_mid.x, center_mid.y, center_mid.z);
        mid_vertices[j].color = dst;

        transformed_pos = XMLoadFloat3(&mid_vertices[j].position);
        transformed_pos = XMVector3Transform(transformed_pos, rotation);
        transformed_pos = XMVector3Transform(transformed_pos, *world);

        XMStoreFloat3(&mid_vertices[j].position, transformed_pos);

        vertices[vertex_idx] = mid_vertices[j];
        vertex_idx++;
    }

    for (int i = 0; i < numStacks; i++)
    {
        float stackAngle = -(i * stackAngleStep);

        for (int j = 0; j < numSlices; j++)
        {
            float sliceAngle = j * sliceAngleStep;

            float x = radius * cosf(stackAngle) * cosf(sliceAngle);
            float y = radius * sinf(stackAngle);
            float z = radius * cosf(stackAngle) * sinf(sliceAngle);

            bot_vertices[i][j].position = Vector3(x, y, z) + Vector3(center_bot.x, center_bot.y, center_bot.z);
            bot_vertices[i][j].color = dst;

            transformed_pos = XMLoadFloat3(&bot_vertices[i][j].position);
            transformed_pos = XMVector3Transform(transformed_pos, rotation);
            transformed_pos = XMVector3Transform(transformed_pos, *world);

            XMStoreFloat3(&bot_vertices[i][j].position, transformed_pos);

            vertices[vertex_idx] = bot_vertices[i][j];
            vertex_idx++;
        }
    }

    vertices[vertex_idx] = bot_vertex;
    vertex_idx++;

    std::vector<uint16_t> indices;

    for (size_t i = 0; i < numStacks; i++)
    {
        for (size_t j = 0; j < numSlices; j++)
        {
            indices.push_back(i * numSlices + j + 1);

            if (j + 1 < numSlices)
                indices.push_back(i * numSlices + j + 2);
            else
                indices.push_back(i * numSlices + 1);
        }
    }

    for (size_t i = 0; i < numSlices; i++)
    {
        indices.push_back(0);
        indices.push_back(numSlices * (numStacks - 1) + i + 1);
    }

    for (size_t i = 0; i < numStacks; i++)
    {
        for (size_t j = 0; j < numSlices; j++)
        {
            if (i + 1 < numStacks)
            {
                indices.push_back(i* numSlices + j + 1);
                indices.push_back((i + 1)* numSlices + j + 1);
            }
        }
    }

    for (size_t i = 0; i < numStacks; i++)
    {
        for (size_t j = 0; j < numSlices; j++)
        {
            indices.push_back(i * numSlices + j + 1 + numSegments + numSlices);

            if (j + 1 < numSlices)
                indices.push_back(i * numSlices + j + 2 + numSegments + numSlices);
            else
                indices.push_back(i * numSlices + 1 + numSegments + numSlices);
        }
    }

    for (size_t i = 0; i < numSlices; i++)
    {
        indices.push_back(numVertices - 1);
        indices.push_back(numSlices * (numStacks - 1) + i + 1 + numSegments + numSlices);
    }

    for (size_t i = 0; i < numStacks; i++)
    {
        for (size_t j = 0; j < numSlices; j++)
        {
            if (i + 1 < numStacks)
            {
                indices.push_back(i * numSlices + j + 1 + numSegments + numSlices);
                indices.push_back((i + 1) * numSlices + j + 1 + numSegments + numSlices);
            }
        }
    }

    for (size_t i = 0; i < numSlices; i++)
    {
        indices.push_back(i + 1 + numSegments);

        if (i + 1 < numSlices)
            indices.push_back(i + 2 + numSegments);
        else
            indices.push_back(1 + numSegments);
    }

    for (size_t i = 0; i < numSlices; i++)
    {
        indices.push_back(i + 1);
        indices.push_back(numSegments + numSlices + i + 1);
    }

    batch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_LINELIST, indices.data(), indices.size(), vertices, numVertices);
}

void XM_CALLCONV DX::DrawSphere(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
    DirectX::XMMATRIX* world, float radius,
    DirectX::GXMVECTOR color)
{
    DX::DrawCapsule(batch, world, Vector3(0, 0, 0), Vector3(0, 0, 0), radius, color);
}

void XM_CALLCONV DX::DrawCylinder(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
    DirectX::XMMATRIX* world, DirectX::SimpleMath::Vector3 pointA, DirectX::SimpleMath::Vector3 pointB, float radius,
    DirectX::GXMVECTOR color, bool fill)
{
    XMFLOAT4 dst;

    if (!fill)
        XMStoreFloat4(&dst, color);
    else
        XMStoreFloat4(&dst, Colors::Black);

    constexpr int numSlices = CYLINDER_SLICES;
    constexpr int numStacks = 1;
    constexpr int numSegments = numSlices * numStacks;
    constexpr int numVertices = (2 * (numSegments + 1));
    constexpr float pi = XM_PI;

    // Calculate vertex positions for the capsule
    VertexPositionColor top_vertex;
    VertexPositionColor bot_vertex;
    VertexPositionColor top_vertices[numSlices];
    VertexPositionColor bot_vertices[numSlices];
    VertexPositionColor vertices[numVertices];
    XMVECTOR transformed_pos;

    XMMATRIX rotation = XMMatrixIdentity();
    rotation = MathHelper::GetRotationFrom2Vectors(pointB, pointA);

    Vector3 center_bot = Vector3(pointA.x, pointA.y, pointA.z);
    Vector3 center_top = Vector3(pointB.x, pointB.y, pointB.z);
    Vector3 center_mid = (pointA + pointB) / 2;

    float stackAngleStep = (pi / 2) / numStacks;
    float sliceAngleStep = (2 * pi) / numSlices;

    transformed_pos = XMLoadFloat3(&center_bot);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);

    XMStoreFloat3(&center_bot, transformed_pos);

    transformed_pos = XMLoadFloat3(&center_mid);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);

    XMStoreFloat3(&center_mid, transformed_pos);

    transformed_pos = XMLoadFloat3(&center_top);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);

    XMStoreFloat3(&center_top, transformed_pos);

    bot_vertex.position = Vector3(center_bot.x, center_bot.y, center_bot.z);
    bot_vertex.color = dst;

    transformed_pos = XMLoadFloat3(&bot_vertex.position);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&bot_vertex.position, transformed_pos);

    top_vertex.position = Vector3(center_top.x, center_top.y, center_top.z);
    top_vertex.color = dst;

    transformed_pos = XMLoadFloat3(&top_vertex.position);
    transformed_pos = XMVector3Transform(transformed_pos, rotation);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&top_vertex.position, transformed_pos);

    int vertex_idx = 0;

    vertices[vertex_idx] = top_vertex;
    vertex_idx++;

    // Draw top hemisphere
    for (int j = 0; j < numSlices; j++)
    {
        float sliceAngle = j * sliceAngleStep;

        float x = radius * cosf(sliceAngle);
        float y = 0;
        float z = radius * sinf(sliceAngle);

        top_vertices[j].position = Vector3(x, y, z) + Vector3(center_top.x, center_top.y, center_top.z);
        top_vertices[j].color = dst;

        transformed_pos = XMLoadFloat3(&top_vertices[j].position);
        transformed_pos = XMVector3Transform(transformed_pos, rotation);
        transformed_pos = XMVector3Transform(transformed_pos, *world);

        XMStoreFloat3(&top_vertices[j].position, transformed_pos);

        vertices[vertex_idx] = top_vertices[j];
        vertex_idx++;
    }

    for (int j = 0; j < numSlices; j++)
    {
        float sliceAngle = j * sliceAngleStep;

        float x = radius * cosf(sliceAngle);
        float y = 0;
        float z = radius * sinf(sliceAngle);

        bot_vertices[j].position = Vector3(x, y, z) + Vector3(center_bot.x, center_bot.y, center_bot.z);
        bot_vertices[j].color = dst;

        transformed_pos = XMLoadFloat3(&bot_vertices[j].position);
        transformed_pos = XMVector3Transform(transformed_pos, rotation);
        transformed_pos = XMVector3Transform(transformed_pos, *world);

        XMStoreFloat3(&bot_vertices[j].position, transformed_pos);

        vertices[vertex_idx] = bot_vertices[j];
        vertex_idx++;
    }

    vertices[vertex_idx] = bot_vertex;
    vertex_idx++;

    std::vector<uint16_t> indices;

    for (size_t j = 0; j < numSlices; j++)
    {
        indices.push_back(0);
        indices.push_back(j + 1);

        indices.push_back(j + 1);

        if (j + 1 < numSlices)
            indices.push_back(j + 2);
        else
            indices.push_back(1);

        indices.push_back(2 * numSlices + 1);
        indices.push_back(j + 1 + numSlices);

        indices.push_back(j + 1 + numSlices);

        if (j + 1 < numSlices)
            indices.push_back(j + 2 + numSlices);
        else
            indices.push_back(1 + numSlices);

        indices.push_back(j + 1);
        indices.push_back(numSlices + j + 1);
    }

    if (fill)
    {
        std::vector<uint16_t> indices_fill;
        VertexPositionColor vertices_fill[numVertices];

        for (int j = 0; j < numSlices; j++)
        {
            if (j + 1 < numSlices)
            {
                indices_fill.push_back(0);
                indices_fill.push_back(j + 1);
                indices_fill.push_back(j + 2);

                indices_fill.push_back(2 * numSlices + 1);
                indices_fill.push_back(j + 1 + numSlices);
                indices_fill.push_back(j + 2 + numSlices);

                indices_fill.push_back(j + 1);
                indices_fill.push_back(j + 2);
                indices_fill.push_back(numSlices + j + 2);

                indices_fill.push_back(j + 1);
                indices_fill.push_back(numSlices + j + 1);
                indices_fill.push_back(numSlices + j + 2);
            }
            else
            {
                indices_fill.push_back(0);
                indices_fill.push_back(j + 1);
                indices_fill.push_back(1);

                indices_fill.push_back(2 * numSlices + 1);
                indices_fill.push_back(j + 1 + numSlices);
                indices_fill.push_back(1 + numSlices);

                indices_fill.push_back(j + 1);
                indices_fill.push_back(1);
                indices_fill.push_back(numSlices + 1);

                indices_fill.push_back(j + 1);
                indices_fill.push_back(numSlices + j + 1);
                indices_fill.push_back(numSlices + 1);
            }
        }

        for (size_t i = 0; i < numVertices; i++)
            vertices[i].color = DirectX::SimpleMath::Vector4(color);

        batch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices_fill.data(), indices_fill.size(), vertices, numVertices);

        for (size_t i = 0; i < numVertices; i++)
            vertices[i].color = SimpleMath::Vector4(Colors::Black);
    }

    batch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_LINELIST, indices.data(), indices.size(), vertices, numVertices);
}

void XM_CALLCONV DX::DrawBox(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
    DirectX::XMMATRIX* world, DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 half_extents,
    DirectX::GXMVECTOR color, bool fill)
{
    VertexPositionColor b1, b2, b3, b4;
    VertexPositionColor t1, t2, t3, t4;

    VertexPositionColor vertices[8];

    XMVECTOR transformed_pos;

    b1.position.x = -half_extents.x;
    b1.position.y = -half_extents.y;
    b1.position.z = half_extents.z;

    b2.position.x = half_extents.x;
    b2.position.y = -half_extents.y;
    b2.position.z = half_extents.z;

    b3.position.x = half_extents.x;
    b3.position.y = -half_extents.y;
    b3.position.z = -half_extents.z;

    b4.position.x = -half_extents.x;
    b4.position.y = -half_extents.y;
    b4.position.z = -half_extents.z;

    t1.position.x = b1.position.x;
    t1.position.y = b1.position.y + 2 * half_extents.y;
    t1.position.z = b1.position.z;

    t2.position.x = b2.position.x;
    t2.position.y = b2.position.y + 2 * half_extents.y;
    t2.position.z = b2.position.z;

    t3.position.x = b3.position.x;
    t3.position.y = b3.position.y + 2 * half_extents.y;
    t3.position.z = b3.position.z;

    t4.position.x = b4.position.x;
    t4.position.y = b4.position.y + 2 * half_extents.y;
    t4.position.z = b4.position.z;

    transformed_pos = XMLoadFloat3(&b1.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&b1.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&b2.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&b2.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&b3.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&b3.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&b4.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&b4.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&t1.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&t1.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&t2.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&t2.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&t3.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&t3.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&t4.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&t4.position, transformed_pos);

    if (!fill)
    {
        b1.color = Vector4(color);
        b2.color = Vector4(color);
        b3.color = Vector4(color);
        b4.color = Vector4(color);

        t1.color = Vector4(color);
        t2.color = Vector4(color);
        t3.color = Vector4(color);
        t4.color = Vector4(color);

        static const WORD s_indices[] =
        {
            0, 1,
            1, 2,
            2, 3,
            3, 0,
            4, 5,
            5, 6,
            6, 7,
            7, 4,
            0, 4,
            1, 5,
            2, 6,
            3, 7,
            0, 5,
            0, 7,
            1, 4,
            1, 6,
            2, 7,
            2, 5,
            3, 4,
            3, 6,
            0, 2,
            1, 3,
            4, 6,
            5, 7
        };

        vertices[0] = b1;
        vertices[1] = b2;
        vertices[2] = b3;
        vertices[3] = b4;
        vertices[4] = t1;
        vertices[5] = t2;
        vertices[6] = t3;
        vertices[7] = t4;

        batch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_LINELIST, s_indices, static_cast<UINT>(std::size(s_indices)), vertices, 8);
    }
    else
    {
        std::vector<uint16_t> indices_fill;

        b1.color = Vector4(color);
        b2.color = Vector4(color);
        b3.color = Vector4(color);
        b4.color = Vector4(color);

        t1.color = Vector4(color);
        t2.color = Vector4(color);
        t3.color = Vector4(color);
        t4.color = Vector4(color);

        vertices[0] = b1;
        vertices[1] = b2;
        vertices[2] = b3;
        vertices[3] = b4;
        vertices[4] = t1;
        vertices[5] = t2;
        vertices[6] = t3;
        vertices[7] = t4;

        indices_fill.push_back(0);
        indices_fill.push_back(1);
        indices_fill.push_back(2);

        indices_fill.push_back(0);
        indices_fill.push_back(2);
        indices_fill.push_back(3);


        indices_fill.push_back(4);
        indices_fill.push_back(5);
        indices_fill.push_back(6);

        indices_fill.push_back(4);
        indices_fill.push_back(6);
        indices_fill.push_back(7);


        indices_fill.push_back(0);
        indices_fill.push_back(4);
        indices_fill.push_back(5);

        indices_fill.push_back(0);
        indices_fill.push_back(2);
        indices_fill.push_back(5);


        indices_fill.push_back(1);
        indices_fill.push_back(5);
        indices_fill.push_back(6);

        indices_fill.push_back(1);
        indices_fill.push_back(3);
        indices_fill.push_back(6);


        indices_fill.push_back(2);
        indices_fill.push_back(6);
        indices_fill.push_back(7);

        indices_fill.push_back(2);
        indices_fill.push_back(3);
        indices_fill.push_back(7);


        indices_fill.push_back(3);
        indices_fill.push_back(7);
        indices_fill.push_back(4);

        indices_fill.push_back(3);
        indices_fill.push_back(0);
        indices_fill.push_back(4);

        batch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, indices_fill.data(), indices_fill.size(), vertices, 8);

        b1.color = Vector4(Colors::Black);
        b2.color = Vector4(Colors::Black);
        b3.color = Vector4(Colors::Black);
        b4.color = Vector4(Colors::Black);

        t1.color = Vector4(Colors::Black);
        t2.color = Vector4(Colors::Black);
        t3.color = Vector4(Colors::Black);
        t4.color = Vector4(Colors::Black);

        static const WORD s_indices[] =
        {
            0, 1,
            1, 2,
            2, 3,
            3, 0,
            4, 5,
            5, 6,
            6, 7,
            7, 4,
            0, 4,
            1, 5,
            2, 6,
            3, 7,
        };

        vertices[0] = b1;
        vertices[1] = b2;
        vertices[2] = b3;
        vertices[3] = b4;
        vertices[4] = t1;
        vertices[5] = t2;
        vertices[6] = t3;
        vertices[7] = t4;

        batch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_LINELIST, s_indices, static_cast<UINT>(std::size(s_indices)), vertices, 8);
    }
}

void XM_CALLCONV DX::DrawBoundingBox(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
    DirectX::XMMATRIX* world, DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 half_extents,
    DirectX::GXMVECTOR color)
{
    VertexPositionColor b1, b2, b3, b4;
    VertexPositionColor t1, t2, t3, t4;

    VertexPositionColor vertices[8];

    XMVECTOR transformed_pos;

    b1.position.x = -half_extents.x;
    b1.position.y = -half_extents.y;
    b1.position.z = half_extents.z;

    b2.position.x = half_extents.x;
    b2.position.y = -half_extents.y;
    b2.position.z = half_extents.z;

    b3.position.x = half_extents.x;
    b3.position.y = -half_extents.y;
    b3.position.z = -half_extents.z;

    b4.position.x = -half_extents.x;
    b4.position.y = -half_extents.y;
    b4.position.z = -half_extents.z;

    t1.position.x = b1.position.x;
    t1.position.y = b1.position.y + 2 * half_extents.y;
    t1.position.z = b1.position.z;

    t2.position.x = b2.position.x;
    t2.position.y = b2.position.y + 2 * half_extents.y;
    t2.position.z = b2.position.z;

    t3.position.x = b3.position.x;
    t3.position.y = b3.position.y + 2 * half_extents.y;
    t3.position.z = b3.position.z;

    t4.position.x = b4.position.x;
    t4.position.y = b4.position.y + 2 * half_extents.y;
    t4.position.z = b4.position.z;

    transformed_pos = XMLoadFloat3(&b1.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&b1.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&b2.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&b2.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&b3.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&b3.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&b4.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&b4.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&t1.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&t1.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&t2.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&t2.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&t3.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&t3.position, transformed_pos);

    transformed_pos = XMLoadFloat3(&t4.position);
    transformed_pos = XMVector3Transform(transformed_pos, *world);

    XMStoreFloat3(&t4.position, transformed_pos);

    b1.color = Vector4(color);
    b2.color = Vector4(color);
    b3.color = Vector4(color);
    b4.color = Vector4(color);

    t1.color = Vector4(color);
    t2.color = Vector4(color);
    t3.color = Vector4(color);
    t4.color = Vector4(color);

    vertices[0] = b1;
    vertices[1] = b2;
    vertices[2] = b3;
    vertices[3] = b4;
    vertices[4] = t1;
    vertices[5] = t2;
    vertices[6] = t3;
    vertices[7] = t4;

    static const WORD s_indices[] =
    {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        4, 5,
        5, 6,
        6, 7,
        7, 4,
        0, 4,
        1, 5,
        2, 6,
        3, 7,
    };

    batch->DrawIndexed(D3D_PRIMITIVE_TOPOLOGY_LINELIST, s_indices, static_cast<UINT>(std::size(s_indices)), vertices, 8);
}

void XM_CALLCONV DX::Draw3DArc(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch,
    DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 center, float radius, float angle, float height, bool is_front,
    DirectX::GXMVECTOR color)
{
    constexpr int sphere_seg = ARC_SLICES;

    float correction = -XM_PI / 2;
    float plane_angle = atan2f(rotation.z, rotation.x);

    Vector3 bottom_vertices_1[sphere_seg];
    Vector3 bottom_vertices_2[sphere_seg];
    Vector3 top_vertices_1[sphere_seg];
    Vector3 top_vertices_2[sphere_seg];
    Vector3 center_vertex;
    Vector3 center_top_vertex;
    Vector3 center_bot_vertex;

    Vector3 center_top = Vector3(center.x, center.y + height, center.z);
    Vector3 center_bot = Vector3(center.x, center.y - height, center.z);

    center_vertex = center;
    center_top_vertex = center_top;
    center_bot_vertex = center_bot;

    if (is_front)
        correction = XM_PI / 2;

    Vector3 start_top = Vector3(center_top.x + cos(plane_angle + correction) * radius, center_top.y, center_top.z + sin(plane_angle + correction) * radius);
    Vector3 start_bot = Vector3(center_bot.x + cos(plane_angle + correction) * radius, center_bot.y, center_bot.z + sin(plane_angle + correction) * radius);

    //Top
    for (size_t i = 0; i < sphere_seg; i++)
    {
        float x = cos(plane_angle + correction - angle / sphere_seg * i) * radius;
        float y = 0;
        float z = sin(plane_angle + correction - angle / sphere_seg * i) * radius;

        top_vertices_1[i] = center_top + Vector3(x, y, z);

        x = cos(plane_angle + correction + angle / sphere_seg * i) * radius;
        y = 0;
        z = sin(plane_angle + correction + angle / sphere_seg * i) * radius;

        top_vertices_2[i] = center_top + Vector3(x, y, z);
    }

    //Bottom
    for (size_t i = 0; i < sphere_seg; i++)
    {
        float x = cos(plane_angle + correction - angle / sphere_seg * i) * radius;
        float y = 0;
        float z = sin(plane_angle + correction - angle / sphere_seg * i) * radius;

        bottom_vertices_1[i] = center_bot + Vector3(x, y, z);

        x = cos(plane_angle + correction + angle / sphere_seg * i) * radius;
        y = 0;
        z = sin(plane_angle + correction + angle / sphere_seg * i) * radius;

        bottom_vertices_2[i] = center_bot + Vector3(x, y, z);
    }

    for (size_t i = 0; i < sphere_seg; i++)
    {
        if (i + 1 < sphere_seg)
        {
            DrawLine(batch, top_vertices_1[i], top_vertices_1[i + 1], color);
            DrawLine(batch, top_vertices_2[i], top_vertices_2[i + 1], color);

            DrawLine(batch, bottom_vertices_1[i], bottom_vertices_1[i + 1], color);
            DrawLine(batch, bottom_vertices_2[i], bottom_vertices_2[i + 1], color);
        }

        DrawLine(batch, bottom_vertices_1[sphere_seg - 1], top_vertices_1[sphere_seg - 1], color);
        DrawLine(batch, bottom_vertices_2[sphere_seg - 1], top_vertices_2[sphere_seg - 1], color);

        DrawLine(batch, bottom_vertices_1[sphere_seg - 1], center_bot_vertex, color);
        DrawLine(batch, bottom_vertices_2[sphere_seg - 1], center_bot_vertex, color);

        DrawLine(batch, top_vertices_1[sphere_seg - 1], top_vertices_1[sphere_seg - 1], color);
        DrawLine(batch, top_vertices_2[sphere_seg - 1], top_vertices_2[sphere_seg - 1], color);

        DrawLine(batch, top_vertices_1[sphere_seg - 1], center_top_vertex, color);
        DrawLine(batch, top_vertices_2[sphere_seg - 1], center_top_vertex, color);

        DrawLine(batch, center_bot_vertex, center_top_vertex, color);
    }
}