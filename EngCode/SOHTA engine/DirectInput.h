#pragma once
#include "Includes.h"
#include "dinput.h"

class DirectInput
{

public:
	bool InitDirectInput(HWND hwnd, HINSTANCE hInstance);
	void Release();

public:
	static IDirectInputDevice8* DIKeyboard;
	static IDirectInputDevice8* DIMouse;

	static DIMOUSESTATE mouseLastState;
	static DIMOUSESTATE mouseCurrState;
	static LPDIRECTINPUT8 directInput;

public:
	static float rotx;
	static float rotz;
	static float scaleX;
	static float scaleY;

	static float moveLeftRight;
	static float moveBackForward;
	static float camYaw;
	static float camPitch;
	static float camPitch2;

private:
	friend class Graphics;
	friend class App;
	friend class StdScene;

private:
	static int sens;
};

