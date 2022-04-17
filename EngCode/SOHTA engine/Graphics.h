#pragma once
#include "Includes.h"
#include "D3D.h"
#include "D2D.h"
#include "Text2D.h"
#include "StdScene.h"
#include "Camera.h"
#include "VideoConfig.h"
#include "RenderQueue_2D.h"
#include "Scene.hpp"

class Graphics : VideoConfig
{
	
public:
	void init(HWND hwnd);
	void startScene();
	void Update(double FrameTime, double FPS);
	void Render();
	void Release();
	
private:
	void InitSharedScreen(IDXGIAdapter1* Adapter);

private:
	D3D* d3d;
	D2D* d2d;

	RenderQueue_2D* RQ2D;
private:
	StdScene* fistscene;

private:
	ID3D10Device1* d3d101Device;
	IDXGIKeyedMutex* keyedMutex11;
	IDXGIKeyedMutex* keyedMutex10;
	ID3D11Texture2D* sharedTex11;
	IDXGISurface1* sharedSurface10;
	
};

