#include "D3D.h"

ID3D11Device* D3D::d3dDevice = NULL;
ID3D11DeviceContext* D3D::d3dDevCon = NULL;
IDXGISwapChain* D3D::SwapChain = NULL;
ID3D11RenderTargetView* D3D::renderTargetView = NULL;
ID3D11DepthStencilView* D3D::depthStencilView = NULL;
ID3D11Texture2D* D3D::depthStencilBuffer = NULL;
IDXGIAdapter1* D3D::Adapter = NULL;