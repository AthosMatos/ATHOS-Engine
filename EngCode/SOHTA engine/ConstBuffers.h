#pragma once
#include "ShaderStrct_Light.h"
#include "ShaderStrct_Vertex.h"

struct cbPerObject
{
	XMMATRIX  WVP;
	XMMATRIX  World;
};

struct cbPerFrame
{
	SLight light[10];
};
