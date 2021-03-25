#pragma once
#include "Includes.h"

struct SLight
{
	SLight()
	{
		ZeroMemory(this, sizeof(SLight));
	}
	XMFLOAT3 dir;
	float range;
	XMFLOAT3 pos;
	float cone;
	XMFLOAT3 att;
	float bait2;
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;
};