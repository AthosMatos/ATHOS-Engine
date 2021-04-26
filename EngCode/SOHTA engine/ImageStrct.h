#pragma once
#include "D2D.h"

struct Images
{
	const wchar_t* name;
	ID2D1Bitmap* bmp;


	Images* next;
	Images* prev;

};