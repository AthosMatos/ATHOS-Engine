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

	float size;

	IDWriteTextFormat* TextFormat;

	ID2D1SolidColorBrush* Brush;
	D2D1_RECT_F rect;

	TextBox* next;
	TextBox* prev;

};