#include "Image.h"

Images* Image::images;

IWICImagingFactory* Image::wicfactory;
IWICBitmapDecoder* Image::wicdecoder;
IWICBitmapFrameDecode* Image::wicframe;
IWICFormatConverter* Image::wicconverter;