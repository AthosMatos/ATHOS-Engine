#include "Image.h"

IWICImagingFactory* Image::wicfactory;
IWICBitmapDecoder* Image::wicdecoder;
IWICBitmapFrameDecode* Image::wicframe;
IWICFormatConverter* Image::wicconverter;