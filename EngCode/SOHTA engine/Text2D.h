#pragma once
#include "D2D.h"

class Text2D : D2D 
{
private:
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

public:
	Text2D();
	Text2D(nullptr_t);

	void Create(const wchar_t* ID);

	void Select(const wchar_t* ID);

	void Update(const wchar_t* ID, float TextSize, int OffsetLeftX, int OffsetTopY, D2D1::ColorF color);
	void Update(float TextSize, int OffsetLeftX, int OffsetTopY, D2D1::ColorF color);

	void Render(const wchar_t* ID, const wchar_t* text);//render specific textbox
	void Render(const wchar_t* text);//render select textbox
	
	void Release();

private:
	void StdFontStyle(TextBox* FT);

private:	
	static TextBox* TB;
	static const wchar_t* SelectedTextBox;
};

