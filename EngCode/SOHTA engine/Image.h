#pragma once
#include "RenderQueue_2D.h"
#include <wincodec.h>

class Image : RenderQueue_2D
{
public:
	Image();

public:
	void Load(const wchar_t* name, const wchar_t* filePath);
	void Update(const wchar_t* name, float Transparency);
	void Draw(const wchar_t* name, bool state);
	void MoveLayerUp(int amount);
	void MoveLayerDown(int amount);
	void Release();

private:
	void LoadImg(const wchar_t* filename);
	void UnloadImg(const wchar_t* name);

private:

	static IWICImagingFactory* wicfactory;
	static IWICBitmapDecoder* wicdecoder;
	static IWICBitmapFrameDecode* wicframe;
	static IWICFormatConverter* wicconverter;
};

