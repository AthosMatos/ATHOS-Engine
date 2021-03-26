#pragma once
#include <wincodec.h>
#include "Includes.h"
#include "D2D.h"

class Image : D2D
{

private:
	struct Images
	{
		const wchar_t* name;
		ID2D1Bitmap* bmp;

		Images* next;
		Images* prev;

	};

public:
	Image();

public:
	void Load(const wchar_t* name, const wchar_t* filePath);
	void Draw(const wchar_t* name);
	
private:
	void LoadImg(const wchar_t* filename);

private:
	Images* images;

	IWICImagingFactory* wicfactory;
	IWICBitmapDecoder* wicdecoder;
	IWICBitmapFrameDecode* wicframe;
	IWICFormatConverter* wicconverter;

};

