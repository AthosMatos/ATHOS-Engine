#pragma once
#include "D2D.h"

struct TextBox
{
	TextBox()
	{
		Brush = NULL;
		TextFormat = NULL;
	}

	const wchar_t* ID;
	const wchar_t* ActualText;
	bool render = false;
	float transparency = 0;

	int fps = 0;
	float size;

	IDWriteTextFormat* TextFormat;

	ID2D1SolidColorBrush* Brush;
	D2D1_RECT_F rect;
};