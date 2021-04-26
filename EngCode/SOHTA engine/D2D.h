#pragma once
#include "Includes.h"
#include "Geometry.h"
#include "D3D.h"
#include "VideoConfig.h"

class D2D : public VideoConfig
{
public:
	D2D();
	D2D(nullptr_t);
	void InitD2D(IDXGISurface1* sharedSurface10);

	void UpdateClassResources(Geometry* obj, D3D* d3d);
	void UpdateClassResources(IDXGIKeyedMutex* keyedMutex11, IDXGIKeyedMutex* keyedMutex10);

	void SetRenderArea(ID3D11Texture2D* sharedTex11,float x0, float x, float y0, float y);
	void CreateDWriteFactory();
	void ClearScreen();
	void Release();

protected:
	void Start2Din3D();
	void End2Din3D();
	void End2Din3D(float Transparency);

protected:
	static ID2D1RenderTarget* D2DRenderTarget;
	
	static ID3D11Buffer* d2dIndexBuffer;
	static ID3D11Buffer* d2dVertBuffer;

	static ID3D11ShaderResourceView* d2dTexture;

	static IDXGIKeyedMutex* keyedMutex11;
	static IDXGIKeyedMutex* keyedMutex10;

	static IDWriteFactory* DWriteFactory;

	Geometry* geo;
	D3D* d3d;
};

