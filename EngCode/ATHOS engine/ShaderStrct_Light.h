#pragma once
#include "Includes.h"

struct SLight
{
	SLight()
	{
		ZeroMemory(this, sizeof(SLight));
	}

	XMFLOAT3 pos;
	float range;
	XMFLOAT3 dir;
	float cone;
	XMFLOAT3 att;
	float specularPower;
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
	XMFLOAT4 specular;
};