#include "Image.h"

Image::Image()
{	
	images = NULL;

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
	if (images == NULL)
	{
		images = (Images*)malloc(sizeof(Images));
		images->next = NULL;
		images->prev = NULL;
		images->bmp = NULL;
		images->name = name;
		
		LoadImg(filePath);

		D2DRenderTarget->CreateBitmapFromWicBitmap(
			wicconverter,
			NULL,
			&images->bmp
		);

		return;
	}
	else
	{
		Images* Nimage;
		Nimage = (Images*)malloc(sizeof(Images));

		Nimage->next = NULL;
		Nimage->bmp = NULL;
		Nimage->name = name;

		LoadImg(filePath);

		D2DRenderTarget->CreateBitmapFromWicBitmap(
			wicconverter,
			NULL,
			&Nimage->bmp
		);

		if (images->next == NULL)
		{
			images->next = Nimage;
			Nimage->prev = images;

			return;
		}
		else
		{
			while (images->next != NULL) { images = images->next; }
			images->next = Nimage;
			Nimage->prev = images;
			while (images->prev != NULL) { images = images->prev; }

			return;
		}
	}

}

void Image::Draw(const wchar_t* name)
{
	Images* Fimages;
	Fimages = images;

	while (Fimages->name != name) { Fimages = Fimages->next; }

	Start2Din3D();

	//Draw D2D content        
	D2DRenderTarget->BeginDraw();

	D2DRenderTarget->DrawBitmap(
		Fimages->bmp,
		D2D1::RectF(0.0f, 0.0f, Fimages->bmp->GetSize().width, Fimages->bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, Fimages->bmp->GetSize().width, Fimages->bmp->GetSize().height)
	);

	D2DRenderTarget->EndDraw();

	End2Din3D();
}

void Image::Draw(const wchar_t* name, float Transparency)
{
	Images* Fimages;
	Fimages = images;

	while (Fimages->name != name) { Fimages = Fimages->next; }

	Start2Din3D();

	//Draw D2D content        
	D2DRenderTarget->BeginDraw();

	D2DRenderTarget->DrawBitmap(
		Fimages->bmp,
		D2D1::RectF(0.0f, 0.0f, Fimages->bmp->GetSize().width, Fimages->bmp->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.0f, 0.0f, Fimages->bmp->GetSize().width, Fimages->bmp->GetSize().height)
	);

	D2DRenderTarget->EndDraw();

	End2Din3D(Transparency);
}

void Image::Release()
{
	Images* Temp;
	Images* TTemp;
	Temp = images;

	while (true)
	{
		if (Temp != NULL)
		{
			TTemp = Temp->next;
			free(Temp);
			Temp = TTemp;
		}
		else break;
	}
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
	Images* Fimages;
	Fimages = images;
	while (Fimages->name != name) { Fimages = Fimages->next; }

	if (Fimages->prev == NULL)
	{
		images = Fimages->next;
		Fimages->next->prev = Fimages->prev;

		free(Fimages);

		return;
	}
	if (Fimages->next == NULL)
	{
		Fimages->prev->next = Fimages->next;

		free(Fimages);

		return;
	}

	Fimages->prev->next = Fimages->next;
	Fimages->next->prev = Fimages->prev;
	free(Fimages);
}
