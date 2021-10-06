#pragma once
#include "win.h"
#include "Graphics.h"
#include "Timer.h"
#include "DirectInput.h"

class App
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
	Win* window;

private:
	Timer timer;
	DirectInput Dinput;

private:
	MSG msg;
	
};

