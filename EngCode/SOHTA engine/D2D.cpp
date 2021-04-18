#include "D2D.h"

D2D::D2D(){}

D2D::D2D(nullptr_t)
{
    D2DRenderTarget = NULL;
    d2dIndexBuffer = NULL;
    d2dVertBuffer = NULL;
    d2dTexture = NULL;
    keyedMutex11 = NULL;
    keyedMutex10 = NULL;
    geo = NULL;
    d3d = NULL;
    DWriteFactory = NULL;
}

void D2D::InitD2D(IDXGISurface1* sharedSurface10)
{

    ID2D1Factory* D2DFactory;
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), (void**)&D2DFactory);

    D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties;

    ZeroMemory(&renderTargetProperties, sizeof(renderTargetProperties));

    renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;
    renderTargetProperties.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);

    hr = D2DFactory->CreateDxgiSurfaceRenderTarget(sharedSurface10, &renderTargetProperties, &D2DRenderTarget);

    sharedSurface10->Release();
    D2DFactory->Release();

    CreateDWriteFactory();

}

void D2D::UpdateClassResources(Geometry* geo, D3D* d3d)
{
    this->geo = geo;
    this->d3d = d3d;
}

void D2D::UpdateClassResources(IDXGIKeyedMutex* keyedMutex11, IDXGIKeyedMutex* keyedMutex10)
{
    this->keyedMutex11 = keyedMutex11;
    this->keyedMutex10 = keyedMutex10;
}

void D2D::SetRenderArea(ID3D11Texture2D* sharedTex11, float x0, float x, float y0, float y)
{
    float LeftXspace;
    float TopYspace;
    float RightXspace;
    float BottomYspace;
        
    if (x0 == 0) LeftXspace = -1.0f;
    else LeftXspace = -1.0f + (x0 / H_res);

    if (y0 == 0) TopYspace = 1.0f;
    else TopYspace = 1.0f - (y0 / V_res);

    if (x == 0) RightXspace = 1.0f;
    else  RightXspace = 1.0f - (x / H_res);

    if (y == 0) BottomYspace = -1.0f;
    else BottomYspace = -1.0f + (y / V_res);
       
    //Create the vertex buffer
    Textured_Vertex v[] =
    {
        // Front Face
        Textured_Vertex(LeftXspace,  BottomYspace, -1.0f, 0.0f, 1.0f),
        Textured_Vertex(LeftXspace,  TopYspace, -1.0f, 0.0f, 0.0f),
        Textured_Vertex(RightXspace,   TopYspace, -1.0f, 1.0f, 0.0f),
        Textured_Vertex(RightXspace,  BottomYspace, -1.0f, 1.0f, 1.0f),
    };


    DWORD indices[] = {
        // Front Face
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
    D3D::d3dDevice->CreateBuffer(&indexBufferDesc, &iinitData, &d2dIndexBuffer);


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
    HRESULT hr = D3D::d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &d2dVertBuffer);

    //Create A shader resource view from the texture D2D will render to,
    //So we can use it to texture a square which overlays our scene
    D3D::d3dDevice->CreateShaderResourceView(sharedTex11, NULL, &d2dTexture);
}

void D2D::CreateDWriteFactory()
{
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&DWriteFactory));
}

void D2D::ClearScreen()
{
    Start2Din3D();

    D2DRenderTarget->BeginDraw();
    D2DRenderTarget->Clear();
    D2DRenderTarget->EndDraw();

    End2Din3D();
}

void D2D::Release()
{  
    if (d2dVertBuffer) d2dVertBuffer->Release();
    if (d2dIndexBuffer) d2dIndexBuffer->Release();
    if (d2dTexture) d2dTexture->Release();
    if(DWriteFactory) DWriteFactory->Release();
}

void D2D::Start2Din3D()
{
    //Release the D3D 11 Device
    keyedMutex11->ReleaseSync(0);

    //Use D3D10.1 device
    keyedMutex10->AcquireSync(0, 5);
}

void D2D::End2Din3D()
{
    keyedMutex10->ReleaseSync(1);

    //Use the D3D11 Device
    keyedMutex11->AcquireSync(1, 5);

    //Use the shader resource representing the direct2d render target
    //to texture a square which is rendered in screen space so it
    //overlays on top of our entire scene. We use alpha blending so
    //that the entire background of the D2D render target is "invisible",
    //And only the stuff we draw with D2D will be visible (the text)

    //Set the blend state for D2D render target texture objects

    d3d->d3dDevCon->IASetInputLayout(geo->vertLayout_tex);
    d3d->d3dDevCon->VSSetShader(geo->VS_tex, 0, 0);
    d3d->d3dDevCon->PSSetShader(geo->PS_clip_O, 0, 0);

    //Set the d2d Index buffer
    d3d->d3dDevCon->IASetIndexBuffer(d2dIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    //Set the d2d vertex buffer
    UINT stride = sizeof(Textured_Vertex);
    UINT offset = 0;
    d3d->d3dDevCon->IASetVertexBuffers(0, 1, &d2dVertBuffer, &stride, &offset);

    XMMATRIX m = XMMatrixIdentity();

    geo->cbPerObj.WVP = XMMatrixTranspose(m);
    geo->cbPerObj.World = XMMatrixTranspose(m);
    d3d->d3dDevCon->UpdateSubresource(geo->cbPerObjectBuffer, 0, NULL, &geo->cbPerObj, 0, 0);
    d3d->d3dDevCon->VSSetConstantBuffers(0, 1, &geo->cbPerObjectBuffer);
    d3d->d3dDevCon->PSSetShaderResources(0, 1, &d2dTexture);

    d3d->d3dDevCon->RSSetState(geo->RS_Transparent2);
    d3d->d3dDevCon->OMSetDepthStencilState(geo->DSLessEqual, 0);

    //Draw 
    d3d->d3dDevCon->DrawIndexed(6, 0, 0);
}



