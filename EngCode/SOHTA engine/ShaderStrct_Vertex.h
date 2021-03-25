#pragma once
#include "Includes.h"

struct Colored_Vertex    //Overloaded Vertex Structure
{
	Colored_Vertex() {}
	Colored_Vertex(float x, float y, float z,
		float cr, float cg, float cb, float ca)
		: pos(x, y, z), color(cr, cg, cb, ca) {}

	XMFLOAT3 pos;
	XMFLOAT4 color;

};

struct Textured_Vertex    //Overloaded Vertex Structure
{
	Textured_Vertex() {}
	Textured_Vertex(float x, float y, float z,
		float u, float v)
		: pos(x, y, z), texCoord(u, v) {}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
};

struct light_Vertex    //Overloaded Vertex Structure
{
	light_Vertex() {}
	light_Vertex(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz)
		: pos(x, y, z), texCoord(u, v), normal(nx, ny, nz) {}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
	XMFLOAT3 normal;
};