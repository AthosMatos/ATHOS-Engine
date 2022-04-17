#pragma once
#include "Geometry.h"

class Sky : private Geometry
{
public:
	Sky();
	void CreateSky(const wchar_t* filepath);
	void CreateSphere(int LatLines, int LongLines);
	void Update();
	void Render();
	void Release();

private:
	int NumSphereVertices;
	int NumSphereFaces;
	ID3D11SamplerState* TexSamplerState;
	XMMATRIX sphereWorld;

private:
	UINT stride = sizeof(light_Vertex);
	UINT offset = 0;
};

