#pragma once
#include "Includes.h"
#include "DirectInput.h"
#include "VideoConfig.h"

class Win : private VideoConfig
{
public:
	Win();
	void StartWin(HINSTANCE hInstance);
	HWND GetHwnd();

private:
	LPCWSTR ClassName;
	HWND hwnd;
	void WClass(HINSTANCE hInstance);

	
};