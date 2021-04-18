#include "Sky.h"

Sky::Sky(){}

void Sky::CreateSky(const wchar_t* filepath)
{
    CreateSphere(10,10);

    ID3D11Texture2D* SMTexture = 0;
    CreateDDSTextureFromFile(d3dDevice, filepath, (ID3D11Resource**)&SMTexture,nullptr);

    D3D11_TEXTURE2D_DESC SMTextureDesc;
    SMTextureDesc.MiscFlags= D3D11_RESOURCE_MISC_TEXTURECUBE;
    SMTexture->GetDesc(&SMTextureDesc);

    D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
    SMViewDesc.Format = SMTextureDesc.Format;
    SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
    SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
    SMViewDesc.TextureCube.MostDetailedMip = 0;

    d3dDevice->CreateShaderResourceView(SMTexture, &SMViewDesc, &smrv);

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    HRESULT hr = d3dDevice->CreateSamplerState(&sampDesc, &TexSamplerState);
}

void Sky::CreateSphere(int LatLines, int LongLines)
{
    NumSphereVertices = ((LatLines - 2) * LongLines) + 2;
    NumSphereFaces = ((LatLines - 3) * (LongLines) * 2) + (LongLines * 2);

    float sphereYaw = 0.0f;
    float spherePitch = 0.0f;

    std::vector<light_Vertex> vertices(NumSphereVertices);

    XMVECTOR currVertPos = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

    vertices[0].pos.x = 0.0f;
    vertices[0].pos.y = 0.0f;
    vertices[0].pos.z = 1.0f;

    for (DWORD i = 0; i < LatLines - 2; ++i)
    {
        spherePitch = (i + 1) * (3.14 / (LatLines - 1));
        Rotationx = XMMatrixRotationX(spherePitch);
        for (DWORD j = 0; j < LongLines; ++j)
        {
            sphereYaw = j * (6.28 / (LongLines));
            Rotationy = XMMatrixRotationZ(sphereYaw);
            currVertPos = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), (Rotationx * Rotationy));
            currVertPos = XMVector3Normalize(currVertPos);
            vertices[i * LongLines + j + 1].pos.x = XMVectorGetX(currVertPos);
            vertices[i * LongLines + j + 1].pos.y = XMVectorGetY(currVertPos);
            vertices[i * LongLines + j + 1].pos.z = XMVectorGetZ(currVertPos);
        }
    }

    vertices[NumSphereVertices - 1].pos.x = 0.0f;
    vertices[NumSphereVertices - 1].pos.y = 0.0f;
    vertices[NumSphereVertices - 1].pos.z = -1.0f;


    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(light_Vertex) * NumSphereVertices;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexBufferData;

    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = &vertices[0];
    d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &sphereVertBuffer);


    std::vector<DWORD> indices(NumSphereFaces * 3);

    int k = 0;
    for (DWORD l = 0; l < LongLines - 1; ++l)
    {
        indices[k] = 0;
        indices[k + 1] = l + 1;
        indices[k + 2] = l + 2;
        k += 3;
    }

    indices[k] = 0;
    indices[k + 1] = LongLines;
    indices[k + 2] = 1;
    k += 3;

    for (DWORD i = 0; i < LatLines - 3; ++i)
    {
        for (DWORD j = 0; j < LongLines - 1; ++j)
        {
            indices[k] = i * LongLines + j + 1;
            indices[k + 1] = i * LongLines + j + 2;
            indices[k + 2] = (i + 1) * LongLines + j + 1;

            indices[k + 3] = (i + 1) * LongLines + j + 1;
            indices[k + 4] = i * LongLines + j + 2;
            indices[k + 5] = (i + 1) * LongLines + j + 2;

            k += 6; // next quad
        }

        indices[k] = (i * LongLines) + LongLines;
        indices[k + 1] = (i * LongLines) + 1;
        indices[k + 2] = ((i + 1) * LongLines) + LongLines;

        indices[k + 3] = ((i + 1) * LongLines) + LongLines;
        indices[k + 4] = (i * LongLines) + 1;
        indices[k + 5] = ((i + 1) * LongLines) + 1;

        k += 6;
    }

    for (DWORD l = 0; l < LongLines - 1; ++l)
    {
        indices[k] = NumSphereVertices - 1;
        indices[k + 1] = (NumSphereVertices - 1) - (l + 1);
        indices[k + 2] = (NumSphereVertices - 1) - (l + 2);
        k += 3;
    }

    indices[k] = NumSphereVertices - 1;
    indices[k + 1] = (NumSphereVertices - 1) - LongLines;
    indices[k + 2] = NumSphereVertices - 2;

    D3D11_BUFFER_DESC indexBufferDesc;
    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(DWORD) * NumSphereFaces * 3;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData;

    iinitData.pSysMem = &indices[0];
    d3dDevice->CreateBuffer(&indexBufferDesc, &iinitData, &sphereIndexBuffer);
}

void Sky::Update()
{
    sphereWorld = XMMatrixIdentity();

    //Define sphereWorld's world space matrix
    XMMATRIX Scale = XMMatrixScaling(5.0f, 5.0f, 5.0f);
    //Make sure the sphere is always centered around camera
    XMMATRIX Translation = XMMatrixTranslation(XMVectorGetX(camPosition), XMVectorGetY(camPosition), XMVectorGetZ(camPosition));

    //Set sphereWorld's world space using the transformations
    sphereWorld = Scale * Translation;
}

void Sky::Render()
{
    d3dDevCon->IASetInputLayout(vertLayout_light);
    d3dDevCon->IASetIndexBuffer(sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    d3dDevCon->IASetVertexBuffers(0, 1, &sphereVertBuffer, &stride, &offset);

    WVP = sphereWorld * camView * camProjection;
    cbPerObj.WVP = XMMatrixTranspose(WVP);
    cbPerObj.World = XMMatrixTranspose(sphereWorld);
    d3dDevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
    d3dDevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
    d3dDevCon->PSSetShaderResources(0, 1, &smrv);
    d3dDevCon->PSSetSamplers(0, 1, &TexSamplerState);

    d3dDevCon->VSSetShader(SKYMAP_VS, 0, 0);
    d3dDevCon->PSSetShader(SKYMAP_PS, 0, 0);
    d3dDevCon->RSSetState(RS_Opaque);
    d3dDevCon->OMSetDepthStencilState(DSLessEqual, 0);
    d3dDevCon->DrawIndexed(NumSphereFaces * 3, 0, 0);
    
}

void Sky::Release()
{
    TexSamplerState->Release();
}
