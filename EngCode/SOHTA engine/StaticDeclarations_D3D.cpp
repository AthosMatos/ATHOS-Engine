#include "D3D.h"

ID3D11Device* D3D::d3dDevice;
ID3D11DeviceContext* D3D::d3dDevCon;
IDXGISwapChain* D3D::SwapChain;
ID3D11RenderTargetView* D3D::renderTargetView;
ID3D11DepthStencilView* D3D::depthStencilView;
ID3D11Texture2D* D3D::depthStencilBuffer;
IDXGIAdapter1* D3D::Adapter;