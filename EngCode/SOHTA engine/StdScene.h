#pragma once
#include "Cubes.h"
#include "PL_Cubes.h"
#include "Ground.h"
#include "DirectInput.h"
#include "Sky.h"
#include "Image.h"
#include "Text2D.h"

#define pressflag_cam pressflag_vector[0]
#define pressflag_fpsshow pressflag_vector[1]

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

	bool test = false;
	bool render = true;
	bool pressflag = false;

private:
	double fps;
	bool show_fps;
	bool pressflag_vector[100];

};

