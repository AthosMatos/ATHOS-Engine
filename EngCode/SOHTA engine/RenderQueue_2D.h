#pragma once
#include "D2D.h"
#include "Text2DStrct.h"
#include "ImageStrct.h"
#include <map>
#include <vector>

class RenderQueue_2D : protected D2D
{
public:
	void Render();

protected:
	static map <const wchar_t*, TextBox> TextsData;
	static map <const wchar_t*, Images> ImagesData;

	static vector <const wchar_t*> RenderOrder;

private:
	void ImageRender(int index);
	void TextRender(int index);
	void CheckTransparency(int index, int limit, float transparency);
};

