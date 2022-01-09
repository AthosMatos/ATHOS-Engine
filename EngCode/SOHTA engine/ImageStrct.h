#pragma once
#include "D2D.h"

struct Images
{
	const wchar_t* name;
	ID2D1Bitmap* bmp;
	D2D1_RECT_F rect;

	bool render;
	float transparency = 0;
};