#include "GdiCapture.h"

GdiCapture::GdiCapture(const CaptureSource& source)
{
	_source = source;
	_bitmapInfo.bmiHeader.biSize = sizeof(_bitmapInfo.bmiHeader);
	_bitmapInfo.bmiHeader.biWidth = source.stride;
	_bitmapInfo.bmiHeader.biHeight = -source.height;
	_bitmapInfo.bmiHeader.biPlanes = 1;
	_bitmapInfo.bmiHeader.biBitCount = 32;
	_bitmapInfo.bmiHeader.biSizeImage = source.stride * source.height * 4;
	_bitmapInfo.bmiHeader.biCompression = BI_RGB;
	_sourceContext = source.client ? GetDC(source.window) : GetWindowDC(source.window);
	_captureContext = CreateCompatibleDC(_sourceContext);
	_captureBitmap = CreateCompatibleBitmap(_sourceContext, source.stride, source.height);
	SelectObject(_captureContext, _captureBitmap);
}

GdiCapture::~GdiCapture()
{
	DeleteObject(_captureBitmap);
	DeleteDC(_captureContext);
	ReleaseDC(_source.window, _sourceContext);
}
