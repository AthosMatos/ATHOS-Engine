#include "Graphics.h"
#include <string.h>

void Graphics::InitGfx(HWND hwnd)
{
    cout << "GRAPHICS STARTED\n";

    d3d = new D3D(nullptr);
    d2d = new D2D(nullptr);

    RQ2D = new RenderQueue_2D;

    fistscene = new StdScene();

    d3d->InitD3D(hwnd);
    d2d->UpdateClassResources(geomtry, d3d);
    InitSharedScreen(d3d->Adapter);
    d2d->InitD2D(sharedSurface10);
    d2d->UpdateClassResources(keyedMutex11, keyedMutex10);
    d3d->Adapter->Release();   
  
    cout << "GRAPHICS LOADED\n";
}

void Graphics::LoadScene()
{ 
    fistscene->LoadScene(); 

    d2d->SetRenderArea(sharedTex11,
                        0,
                        0,
                        0,
                        0);
}

void Graphics::Update(double FrameTime, double FPS)
{
    Input();
    fistscene->SceneInput(FrameTime); 
    fistscene->UpdateScene(FrameTime,FPS);
}

void Graphics::Render()
{   
    //bckground color
    float bgColor[4] = { 0.0f,0.05f,0.1f,1.0f };
    //Clear our backbuffer
    d3d->d3dDevCon->ClearRenderTargetView(d3d->renderTargetView, bgColor);
    d3d->d3dDevCon->ClearDepthStencilView(d3d->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    fistscene->Renderscene();

    RQ2D->Render();
    d3d->SwapChain->Present(0, 0);
}

void Graphics::Release()
{
    if (d3d101Device)d3d101Device->Release();
    if (keyedMutex11)keyedMutex11->Release();
    if (keyedMutex10)keyedMutex10->Release();
    if (sharedTex11)sharedTex11->Release();
    if (sharedSurface10)sharedSurface10->Release();
    if (d2d)d2d->Release();
    if (geomtry)geomtry->Release();   
    if (d3d)d3d->Release();    
    if (fistscene)fistscene->Release();
    if (RQ2D)RQ2D->Release();
}

void Graphics::Input()
{
 

}
/////////////////////////// private///////////////////////////////////////

bool Graphics::InitSharedScreen(IDXGIAdapter1* Adapter)
{
    //Create our Direc3D 10.1 Device///////////////////////////////////////////////////////////////////////////////////////
    HRESULT hr = D3D10CreateDevice1(Adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_BGRA_SUPPORT,
        D3D10_FEATURE_LEVEL_9_3, D3D10_1_SDK_VERSION, &d3d101Device);

    //Create Shared Texture that Direct3D 10.1 will render on//////////////////////////////////////////////////////////////
    D3D11_TEXTURE2D_DESC sharedTexDesc;

    ZeroMemory(&sharedTexDesc, sizeof(sharedTexDesc));

    sharedTexDesc.Width = H_res;
    sharedTexDesc.Height = V_res;
    sharedTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sharedTexDesc.MipLevels = 1;
    sharedTexDesc.ArraySize = 1;
    sharedTexDesc.SampleDesc.Count = 1;
    sharedTexDesc.Usage = D3D11_USAGE_DEFAULT;
    sharedTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    sharedTexDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;

    hr = d3d->d3dDevice->CreateTexture2D(&sharedTexDesc, NULL, &sharedTex11);

    // Get the keyed mutex for the shared texture (for D3D11)///////////////////////////////////////////////////////////////
    hr = sharedTex11->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&keyedMutex11);

    // Get the shared handle needed to open the shared texture in D3D10.1///////////////////////////////////////////////////
    IDXGIResource* sharedResource10;
    HANDLE sharedHandle10;

    hr = sharedTex11->QueryInterface(__uuidof(IDXGIResource), (void**)&sharedResource10);

    hr = sharedResource10->GetSharedHandle(&sharedHandle10);

    sharedResource10->Release();

    // Open the surface for the shared texture in D3D10.1///////////////////////////////////////////////////////////////////

    hr = d3d101Device->OpenSharedResource(sharedHandle10, __uuidof(IDXGISurface1), (void**)(&sharedSurface10));

    hr = sharedSurface10->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&keyedMutex10);

    d3d101Device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
    return true;
}






