#include "Graphics.h"
#include <string.h>

#define pressflag_cam pressflag[0]
#define pressflag_fpsshow pressflag[1]

Graphics::Graphics()
{
    d3d = new D3D(nullptr);
    d2d = new D2D(nullptr);
    TXT = new Text2D(nullptr);

    show_fps = false;
    for (int x=0;x<100;x++)
    {
        pressflag[x] = 0;
    }
 
    fistscene = new StdScene();
}

void Graphics::InitGfx(HWND hwnd)
{
    cout << "GRAPHICS STARTED\n";

    d3d->InitD3D(hwnd);
    d2d->UpdateClassResources(geomtry, d3d);
    InitSharedScreen(d3d->Adapter);
    d2d->InitD2D(sharedSurface10);
    d2d->UpdateClassResources(keyedMutex11, keyedMutex10);
    d3d->Adapter->Release();   

    camera = new Camera(nullptr);
    cam = L"CAM1";
  
    cout << "GRAPHICS LOADED\n";
}

void Graphics::LoadScene()
{
    camera->Create(L"CAM1");
    camera->Create(L"CAM2");
    camera->UseCam(cam);
    // camera->Set_FOV(50.0f);

    fistscene->LoadScene();

    TXT->Create(L"FPS");
    TXT->Create(L"AlphaInfo");
    TXT->Create(L"Info");
    TXT->Create(L"Info2");
    TXT->Create(L"cam");

    TXT->Update(L"FPS", 40.0f, 50, 500, D2D1::ColorF::Yellow);  
    TXT->Update(L"AlphaInfo", 15.0f, 680, 520, D2D1::ColorF::White);
    TXT->Update(L"Info", 15.0f, 700, 10, D2D1::ColorF::White);
    TXT->Update(L"cam", 30.0f, 0, 0, D2D1::ColorF::Red);


    d2d->SetRenderArea(sharedTex11,
                        0,
                        0,
                        0,
                        0);
}

void Graphics::Update(double FrameTime, double FPS)
{
    fps = FPS;
    Input();
    fistscene->SceneInput(FrameTime); 
    
    camera->Update(cam);
  
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
   
    d2d->ClearScreen();

    if (show_fps)
    {
        std::wostringstream variableFPS;
        variableFPS << "FPS:" << fps;
        TXT->Render(L"FPS", variableFPS.str().c_str());
        variableFPS.flush();
    }
    Debug_info();

    d3d->SwapChain->Present(0, 0);
}

void Graphics::Release()
{
    if (d3d101Device)d3d101Device->Release();
    if (keyedMutex11)keyedMutex11->Release();
    if (keyedMutex10)keyedMutex10->Release();
    if (BackBuffer11)BackBuffer11->Release();
    if (sharedTex11)sharedTex11->Release();
    if (sharedSurface10)sharedSurface10->Release();
    if (d2d)d2d->Release();
    if (geomtry)geomtry->Release();   
    if (d3d)d3d->Release();    
    if (fistscene)fistscene->Release();
    if (TXT)TXT->Release();
    if (camera)camera->Release();
}

void Graphics::Input()
{
    BYTE keyboardState[256];

    DI.DIKeyboard->Acquire();
   
    DI.DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

    ///camera change flag
    if (keyboardState[DIK_O] & 0x80)
    {
        if (pressflag_cam == 0)
        {
            if (cam != L"CAM2")cam = L"CAM2";
            else cam = L"CAM1";

            camera->UseCam(cam);
        }
        pressflag_cam = 1;
    }
    else if (!(keyboardState[DIK_O] & 0x80)) pressflag_cam = 0;


    ///fps show flag
    if (keyboardState[DIK_Z] & 0x80)
    {
        if (pressflag_fpsshow == 0)
        {
            if (!show_fps) show_fps = true;
            else if (show_fps) show_fps = false;

            d2d->ClearScreen();
        }
        pressflag_fpsshow = 1;
    }
    else if (!(keyboardState[DIK_Z] & 0x80)) pressflag_fpsshow = 0;

}


/////////////////////////// private///////////////////////////////////////

bool Graphics::InitSharedScreen(IDXGIAdapter1* Adapter)
{
    //Create our Direc3D 10.1 Device///////////////////////////////////////////////////////////////////////////////////////
    HRESULT hr = D3D10CreateDevice1(Adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_DEBUG | D3D10_CREATE_DEVICE_BGRA_SUPPORT,
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

void Graphics::Debug_info()
{
    TXT->Render(L"AlphaInfo", L"SOTHA engine Ultra_Alpha_Beta");
    TXT->Render(L"Info", L"PRESS 'Z' TO SEE FPS\nPRESS 'O' TO CHANGE CAMERA");
    TXT->Render(L"cam", cam);
}






