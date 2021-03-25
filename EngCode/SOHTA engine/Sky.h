#pragma once
#include "Geometry.h"

class Sky : private Geometry
{
public:
	Sky();
	void CreateSky();
	void CreateSphere(int LatLines, int LongLines);
	void Update();
	void Render();

private:
	int NumSphereVertices;
	int NumSphereFaces;
	ID3D11SamplerState* TexSamplerState;
	XMMATRIX sphereWorld;
};

