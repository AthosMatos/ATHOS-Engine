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

class Graphics : private VideoConfig
{
public:
	Graphics();
	void InitGfx(HWND hwnd);
	void LoadScene();
	void Update(double FrameTime, double FPS);
	void Render();
	void Release();
	void Input();

	D3D* d3d;
	Camera* camera;

private:
	bool InitSharedScreen(IDXGIAdapter1* Adapter);
	void Debug_info();

private:
	Geometry* geomtry;
	D2D* d2d;

	Text2D* TXT;

	StdScene* fistscene;
	DirectInput DI;

	const wchar_t* cam;
private:
	ID3D10Device1* d3d101Device;
	IDXGIKeyedMutex* keyedMutex11;
	IDXGIKeyedMutex* keyedMutex10;
	ID3D11Texture2D* BackBuffer11;
	ID3D11Texture2D* sharedTex11;
	IDXGISurface1* sharedSurface10;
	
private:
	double fps;
	bool show_fps;
	bool pressflag[100];
	
};

