#pragma once
#include "Cubes.h"
#include "PL_Cubes.h"
#include "Ground.h"
#include "DirectInput.h"
#include "Sky.h"
#include "Image.h"

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
	Image* image;
	CubeS* cubes;
	PL_Cubes* Lightcubes;
	Ground* GridGround;
	Sky* sky;
	float rot=0;
	DirectInput DI;
	int sens = 10;

};

