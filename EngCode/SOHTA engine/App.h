#pragma once
#include "win.h"
#include "Graphics.h"
#include "Timer.h"
#include "DirectInput.h"
#include "VideoConfig.h"

class App : private VideoConfig
{
public:
	App();
	void StartApp(HINSTANCE hInstance);
	void RunApp();
	void EndApp();
	bool Input();

private:
	int frameCount = 0;
	int fps = 0;

private:
	Graphics* Gfx;
	Win window;
	Timer timer;
	MSG msg;
	DirectInput Dinput;
};

