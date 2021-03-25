#include "Image.h"

Image::Image()
{	
	CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicfactory
	);

}

void Image::Load()
{
}
