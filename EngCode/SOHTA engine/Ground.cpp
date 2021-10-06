#include "Ground.h"

Ground::Ground()
{
    grd = NULL;
    squareIndexBuffer = NULL;
    squareVertBuffer = NULL;
}

void Ground::CreateGround(const wchar_t* GrdName, const wchar_t* texpath)
{
    if (grd == NULL)
    {
        grd = (Model*)malloc(sizeof(Model));
        grd->Texture = NULL;
        grd->TexSamplerState = NULL;

        grd->name = GrdName;

        grd->next = NULL;
        grd->prev = NULL;

        CreateTexture(grd, texpath);
        return;
    }
    else
    {
        Model* Ngrd;
        Ngrd = (Model*)malloc(sizeof(Model));
        Ngrd->next = NULL;
        Ngrd->name = GrdName;
        CreateTexture(Ngrd, texpath);

        if (grd->next == NULL)
        {
            grd->next = Ngrd;
            Ngrd->prev = grd;
            return;
        }
        else 
        {
            while (grd->next != NULL) { grd = grd->next; }

            grd->next = Ngrd;
            Ngrd->prev = grd;

            while (grd->prev != NULL) { grd = grd->prev; }
            return;
        }
    }
}

void Ground::UpdateGround(const wchar_t* GrdName, XMVECTOR rotaxis, float rot, bool ActivateTranslation, XMFLOAT3 pos, bool ActivateScale, int size)
{
    Model* fgrd;
    fgrd = grd;

    while (fgrd->name != GrdName) { fgrd = fgrd->next; }

    fgrd->modelWorld = XMMatrixIdentity();
    fgrd->Translation = XMMatrixTranslation(pos.x / size, pos.y / size, pos.z / size);
    fgrd->Scale = XMMatrixScaling(10.0f * size, 1.0f, 10.0f * size); ///gridsetup, this may change if the ground texture is another tex
    fgrd->Rotation = XMMatrixRotationAxis(rotaxis, rot);
    fgrd->size = size;

    if (ActivateTranslation == true && ActivateScale == true && rot == 0) fgrd->modelWorld = fgrd->Translation * fgrd->Scale;
    else if (ActivateTranslation == true && ActivateScale == true && rot != 0) fgrd->modelWorld = fgrd->Translation * fgrd->Rotation * fgrd->Scale;
    else if (ActivateTranslation == true && ActivateScale == false && rot != 0) fgrd->modelWorld = fgrd->Translation * fgrd->Rotation;
    else if (ActivateTranslation == true && ActivateScale == false && rot == 0) fgrd->modelWorld = fgrd->Translation;
    else if (ActivateTranslation == false && ActivateScale == true && rot != 0) fgrd->modelWorld = fgrd->Rotation * fgrd->Scale;
    else if (ActivateTranslation == false && ActivateScale == true && rot == 0) fgrd->modelWorld = fgrd->Scale;
    else fgrd->modelWorld = fgrd->Rotation;
  
}

void Ground::RenderGround(const wchar_t* GrdName)
{
    Model* fgrd;
    fgrd = grd;

    while (fgrd->name != GrdName) { fgrd = fgrd->next; }

    CreateGrdIndexBuffer();
    CreateVertexBuffer_Grd();
    
    //Set the Input Layout
    d3dDevCon->IASetInputLayout(vertLayout_tex);

    d3dDevCon->VSSetShader(VS_tex, 0, 0);
    d3dDevCon->PSSetShader(PS_clip_T, 0, 0);

    d3dDevCon->PSSetShaderResources(0, 1, &grd->Texture);
    d3dDevCon->PSSetSamplers(0, 1, &grd->TexSamplerState);

    WVP = grd->modelWorld * camView * camProjection;
    cbPerObj.World = XMMatrixTranspose(grd->modelWorld);
    cbPerObj.WVP = XMMatrixTranspose(WVP);
    d3dDevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
    d3dDevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);

    d3dDevCon->OMSetBlendState(0, 0, 0xffffffff);
    d3dDevCon->OMSetDepthStencilState(DSLess, 0);
    d3dDevCon->RSSetState(RS_Opaque);
    d3dDevCon->DrawIndexed(6, 0, 0);
}

void Ground::Release()
{
    if (squareVertBuffer)squareVertBuffer->Release();
    if (squareIndexBuffer)squareIndexBuffer->Release();

    Model* Temp = grd;
    Model* TTemp;

    while (true)
    {
        if (Temp != NULL)
        {
            TTemp = Temp->next;
            free(Temp);
            Temp = TTemp;
        }
        else break;
    }
}

void Ground::CreateGrdIndexBuffer()
{
    DWORD indices[] =
    {   // Front Face
        0,  1,  2,
        0,  2,  3,
    };

    D3D11_BUFFER_DESC indexBufferDesc;
    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitData;

    iinitData.pSysMem = indices;
    d3dDevice->CreateBuffer(&indexBufferDesc, &iinitData, &squareIndexBuffer);

    d3dDevCon->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    squareIndexBuffer->Release();
}

void Ground::CreateVertexBuffer_Grd()
{
    Textured_Vertex v[] =
    {
        // Textured_Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 2.0f * grd->size),
       //Textured_Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
       //Textured_Vertex(1.0f, 1.0f,  1.0f, 2.0f * grd->size, 0.0f),
       //Textured_Vertex(1.0f, 1.0f, -1.0f, 2.0f * grd->size, 2.0f * grd->size),
        Textured_Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
        Textured_Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
        Textured_Vertex(1.0f, 1.0f,  1.0f, 1.0f , 0.0f),
        Textured_Vertex(1.0f, 1.0f, -1.0f, 1.0f , 1.0f),
    };

    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(Textured_Vertex) * 4;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexBufferData;

    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = v;
    HRESULT hr = d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &squareVertBuffer);

    UINT stride = sizeof(Textured_Vertex);
    UINT offset = 0;
    d3dDevCon->IASetVertexBuffers(0, 1, &squareVertBuffer, &stride, &offset);
    
    squareVertBuffer->Release();
}

void Ground::CreateTexture(Model* grd, const wchar_t* texPath)
{
    CreateWICTextureFromFile(d3dDevice, texPath, nullptr, &grd->Texture, 0);

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    HRESULT hr = d3dDevice->CreateSamplerState(&sampDesc, &grd->TexSamplerState);
}
