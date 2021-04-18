#include "D2D.h"

IDXGIKeyedMutex* D2D::keyedMutex11;
IDXGIKeyedMutex* D2D::keyedMutex10;
ID2D1RenderTarget* D2D::D2DRenderTarget;
ID3D11Buffer* D2D::d2dIndexBuffer;
ID3D11Buffer* D2D::d2dVertBuffer;
ID3D11ShaderResourceView* D2D::d2dTexture;
IDWriteFactory* D2D::DWriteFactory;