#include "D2D.h"

IDXGIKeyedMutex* D2D::keyedMutex11 = NULL;
IDXGIKeyedMutex* D2D::keyedMutex10 = NULL;
ID2D1RenderTarget* D2D::D2DRenderTarget = NULL;
ID3D11Buffer* D2D::d2dIndexBuffer = NULL;
ID3D11Buffer* D2D::d2dVertBuffer = NULL;
ID3D11ShaderResourceView* D2D::d2dTexture = NULL;
IDWriteFactory* D2D::DWriteFactory = NULL;