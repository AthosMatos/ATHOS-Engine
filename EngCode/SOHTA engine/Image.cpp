#include "Image.h"

Image::Image()
{	
	wicfactory = NULL;
	wicdecoder - NULL;
	wicframe = NULL;
	wicconverter = NULL;

	CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicfactory
	);

}

void Image::Load(const wchar_t* name, const wchar_t* filePath)
{
	LoadImg(filePath);

	Images image;
	image.name = name;

	D2DRenderTarget->CreateBitmapFromWicBitmap(
		wicconverter,
		NULL,
		&image.bmp);

	ImagesData.insert(pair <const wchar_t*, Images>(name, image));
	RenderOrder.insert(RenderOrder.begin(), name);
}

void Image::Update(const wchar_t* name, float Transparency)
{
	ImagesData[name].transparency = Transparency;
}

void Image::Draw(const wchar_t* name, bool state)
{
	ImagesData[name].render = state;
}

void Image::MoveLayerUp(int amount)
{

}

void Image::MoveLayerDown(int amount)
{

}


void Image::Release()
{
	ImagesData.clear();

	if (wicconverter)wicconverter->Release();
	if (wicframe)wicframe->Release();
	if (wicdecoder)wicdecoder->Release();
	if (wicfactory)wicfactory->Release();
}

void Image::LoadImg(const wchar_t* filename)
{
	wicfactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicdecoder
	);

	wicdecoder->GetFrame(0, &wicframe);

	wicfactory->CreateFormatConverter(&wicconverter);

	wicconverter->Initialize(
		wicframe,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);
	
}

void Image::UnloadImg(const wchar_t* name)
{
	ImagesData.erase(name);
}
