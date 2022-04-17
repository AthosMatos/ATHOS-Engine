#include "D3D.h"
#include <DirectXMath.h>

void D3D::InitD3D(HWND hwnd)
{
    cout << "DIRECT3D STARTED\n";
    
    CreateDevice();
    CreateSwapC(hwnd);

    //Create our BackBuffer
    ID3D11Texture2D* BackBuffer;
    HRESULT hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

    //Create our Render Target
    hr = d3dDevice->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
    BackBuffer->Release();

    CreateDSbuffer();
    SetViewport(0.0f,   //x0
                0.0f,   //y0
                0.0f,   //x 
                0.0f);  //y

    cout << "DIRECT3D LOADED\n";
}

void D3D::Release()
{
    if (d3dDevice)d3dDevice->Release();
    if (d3dDevCon)d3dDevCon->Release();
    SwapChain->SetFullscreenState(false, NULL);
    if (SwapChain)SwapChain->Release();
    if (renderTargetView)renderTargetView->Release();
    if (depthStencilView)depthStencilView->Release();
    if (depthStencilBuffer)depthStencilBuffer->Release();
    if (Adapter) Adapter->Release();
    
}

void D3D::CreateViewport(float LeftXspace, float TopYspace, float RightXspace, float BottomYspace)
{
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = LeftXspace;
    viewport.TopLeftY = TopYspace;
    viewport.Width = (float)H_res - (RightXspace + LeftXspace);
    viewport.Height = (float)V_res - (BottomYspace + TopYspace);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    d3dDevCon->RSSetViewports(1, &viewport);
}

void D3D::SetViewport(float x0, float y0, float x, float y)
{
    //VIEWPORT
    // LeftXspace = x0; //space from the left X border in Pixels
    //TopYspace = y0; //space from the top Y border in Pixels
    // RightXspace = x; //space from the right X border in Pixels
    // BottomYspace = y; //space from the bottom Y border in Pixels

    CreateViewport(x0,y0,x,y);
}

UINT D3D::CheckMSAAQuality()
{
    ///CHECK 4X MSAA
    UINT m4xMsaaQuality;
    HRESULT hr=d3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
    assert(m4xMsaaQuality > 0);

    return m4xMsaaQuality;
}

void D3D::CreateDevice()
{
    IDXGIFactory1* DXGIFactory;
    HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&DXGIFactory);
    hr = DXGIFactory->EnumAdapters1(0, &Adapter);
    DXGIFactory->Release();

    D3D_FEATURE_LEVEL DxVersion;
    DxVersion = D3D_FEATURE_LEVEL_11_0;

    hr = D3D11CreateDevice(
        Adapter, // default adapter
        D3D_DRIVER_TYPE_UNKNOWN,
        0, // no software device
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        0, 0, // default feature level array
        D3D11_SDK_VERSION,
        &d3dDevice,
        &DxVersion,
        &d3dDevCon);
}

void D3D::CreateSwapC(HWND hwnd)
{
    //Describe our SwapChain
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

    if (Enable4xMSAA)
    {
        swapChainDesc.SampleDesc.Count = 4;
        swapChainDesc.SampleDesc.Quality = (CheckMSAAQuality() - 1);
    }
    else
    {
        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;
    }
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.Windowed = Windowed;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    //Describe our SwapChain Buffer
    DXGI_MODE_DESC bufferDesc;
    ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

    bufferDesc.Width = H_res;
    bufferDesc.Height = V_res;
    bufferDesc.RefreshRate.Numerator = 60;
    bufferDesc.RefreshRate.Denominator = 1;
    bufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    swapChainDesc.BufferDesc = bufferDesc;

    IDXGIDevice* dxgiDevice = 0;
    HRESULT hr = d3dDevice->QueryInterface(__uuidof(IDXGIDevice),
        (void**)&dxgiDevice);
    IDXGIAdapter* dxgiAdapter = 0;
    hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter),
        (void**)&dxgiAdapter);
    // Finally got the IDXGIFactory interface.
    IDXGIFactory* dxgiFactory = 0;
    hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
        (void**)&dxgiFactory);
    // Now, create the swap chain.

    hr = dxgiFactory->CreateSwapChain(d3dDevice, &swapChainDesc, &SwapChain);
    // Release our acquired COM interfaces (because we are done with them).
    dxgiDevice->Release();
    dxgiAdapter->Release();
    dxgiFactory->Release();
}

void D3D::CreateDSbuffer()
{
    //Describe our Depth/Stencil Buffer
    D3D11_TEXTURE2D_DESC depthStencilDesc;

    depthStencilDesc.Width = H_res;
    depthStencilDesc.Height = V_res;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    if (Enable4xMSAA)
    {
        depthStencilDesc.SampleDesc.Count = 4;
        depthStencilDesc.SampleDesc.Quality = (CheckMSAAQuality() - 1);
    }
    else
    {
        depthStencilDesc.SampleDesc.Count = 1;
        depthStencilDesc.SampleDesc.Quality = 0;
    }
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;

    //Create the Depth/Stencil View
    d3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
    d3dDevice->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

    //Set our Render Target
    d3dDevCon->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
}
