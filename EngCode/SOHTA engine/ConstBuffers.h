#pragma once
#include "ShaderStrct_Light.h"
#include "ShaderStrct_Vertex.h"
#include <vector>

struct cbPerObject
{
	XMMATRIX  WVP;
	XMMATRIX  World;
};

struct cbPerFrame
{
	SLight light[100];
};
