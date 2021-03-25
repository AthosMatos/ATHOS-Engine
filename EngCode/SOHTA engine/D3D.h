#pragma once
#include "Includes.h"
#include "DirectInput.h"
#include "VideoConfig.h"

class D3D : private VideoConfig
{
public:
	D3D();
	D3D(nullptr_t);
	void InitD3D(HWND hwnd);
	void SetViewport(float OffsetLeftX, float OffsetTopY, float OffsetBottonX, float OffsetRightY);
	void Release();

private:
	void CreateViewport(float LeftXspace, float TopYspace, float RightXspace, float BottomYspace);
	UINT CheckMSAAQuality();
	void CreateDevice();
	void CreateSwapC();
	void CreateDSbuffer();

protected:
	static ID3D11Device* d3dDevice;
	static ID3D11DeviceContext* d3dDevCon;
	static IDXGISwapChain* SwapChain;
	static ID3D11RenderTargetView* renderTargetView;
	static ID3D11DepthStencilView* depthStencilView;
	static ID3D11Texture2D* depthStencilBuffer;
	static IDXGIAdapter1* Adapter;	

private:
	friend class D2D;
	friend class Text2D;
	friend class Graphics;
	friend class App;
	friend class StdScene;

	HWND chwnd;

};

