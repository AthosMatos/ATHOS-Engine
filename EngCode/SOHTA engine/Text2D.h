#pragma once
#include "Text2DStrct.h"

class Text2D : D2D 
{
public:
	Text2D();
	Text2D(nullptr_t);

public:
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

