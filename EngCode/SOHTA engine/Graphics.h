#pragma once
#include "Includes.h"
#include "D3D.h"
#include "D2D.h"
#include "Text2D.h"
#include <cstdlib>
#include <ctime>
#include "StdScene.h"
#include "Camera.h"
#include "VideoConfig.h"
#include "RenderQueue_2D.h"

class Graphics : VideoConfig
{
public:
	void InitGfx(HWND hwnd);
	void LoadScene();
	void Update(double FrameTime, double FPS);
	void Render();
	void Release();
	
private:
	void Input();
	bool InitSharedScreen(IDXGIAdapter1* Adapter);

private:
	D3D* d3d;
	D2D* d2d;

	Geometry* geomtry;

	StdScene* fistscene;
	DirectInput DI;

	RenderQueue_2D* RQ2D;

private:
	ID3D10Device1* d3d101Device;
	IDXGIKeyedMutex* keyedMutex11;
	IDXGIKeyedMutex* keyedMutex10;
	ID3D11Texture2D* sharedTex11;
	IDXGISurface1* sharedSurface10;
	
};

