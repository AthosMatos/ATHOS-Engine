#pragma once
#include "RenderQueue_2D.h"

using namespace std;

class Text2D : RenderQueue_2D 
{

public:
	void Create(const wchar_t* ID);

	void Update(const wchar_t* ID, const wchar_t* text, float TextSize, int left, int top, D2D1::ColorF color, float Transparency);
	void Update(const wchar_t* ID, const wchar_t* text, float TextSize, int left, int top, int right, int bottom, D2D1::ColorF color, float Transparency);

	void Update(const wchar_t* ID, const wchar_t* text, int fps, float TextSize, int left, int top, D2D1::ColorF color, float Transparency);
	void Update(const wchar_t* ID, const wchar_t* text, int fps, float TextSize, int left, int top, int right, int bottom, D2D1::ColorF color, float Transparency);

	void Render(const wchar_t* ID, bool state);

	void Release();

private:
	void StdFontStyle(TextBox& FT);

	/*
	
	*/
};

