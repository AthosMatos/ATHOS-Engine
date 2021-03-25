#pragma once
#include <wincodec.h>
#include "Includes.h"
#include "D2D.h"

class Image : D2D
{
public:
	Image();

public:
	void Load();
	
private:
	ID2D1Bitmap* bmp;
	IWICImagingFactory* wicfactory;

};

