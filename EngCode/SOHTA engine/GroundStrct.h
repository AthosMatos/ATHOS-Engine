#pragma once
#include "Geometry.h"

struct GRD
{
	const wchar_t* name;

	XMMATRIX World;
	XMMATRIX Rotation;
	XMMATRIX Scale;
	XMMATRIX Translation;

	int size;

	ID3D11ShaderResourceView* Texture;
	ID3D11SamplerState* TexSamplerState;

	GRD* next;
	GRD* prev;

};