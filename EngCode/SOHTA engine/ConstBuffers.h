#pragma once
#include "ShaderStrct_Light.h"
#include "ShaderStrct_Vertex.h"
#include <vector>

struct cbPerObject
{
	XMMATRIX  WVP;
	XMMATRIX  World;

	XMFLOAT3 cameraPosition;

	XMFLOAT4 difColor;
	bool hasTexture;
};

struct cbPerFrame
{
	SLight light[100];
};



