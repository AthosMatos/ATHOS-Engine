#pragma once
#include "ImageStrct.h"
#include <wincodec.h>

class Image : D2D
{
public:
	Image();

public:
	void Load(const wchar_t* name, const wchar_t* filePath);
	void Draw(const wchar_t* name);
	void Draw(const wchar_t* name,float Transparency);
	void Release();

private:
	void LoadImg(const wchar_t* filename);
	void UnloadImg(const wchar_t* name);

private:
	static Images* images;

	static IWICImagingFactory* wicfactory;
	static IWICBitmapDecoder* wicdecoder;
	static IWICBitmapFrameDecode* wicframe;
	static IWICFormatConverter* wicconverter;
};

