#pragma once
#include "Cubes.h"
#include "PL_Cubes.h"
#include "Ground.h"
#include "DirectInput.h"
#include "Sky.h"
#include "Image.h"
#include "Text2D.h"

using namespace std;

class StdScene 
{
public:
	void LoadScene();
	void UpdateScene(double frametime, double FPS);
	void Renderscene();
	void Release();
	void SceneInput(double frametime);
	void StdNoClipMouse(DIMOUSESTATE mcs);
	void ShowMicePosDebug(bool show);

private:
	void Debug_info();

private:
	Image* image;
	CubeS* cubes;
	Camera* camera;
	PL_Cubes* Lightcubes;

	Ground* GridGround;
	Sky* sky;
	float rot = 0;
	DirectInput DI;
	int sens = 10;
	Text2D* TXT;

	const wchar_t* cam;

	struct keydata
	{
		bool isPressing = false;
		bool Pressed = false;
		int toggle = 0;
	};

private:
	double fps;
	bool show_fps;
	map <string,bool> pressflag;

	map <string, keydata> KeyState;

};

