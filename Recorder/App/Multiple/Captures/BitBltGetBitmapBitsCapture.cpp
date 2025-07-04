#include "BitBltGetBitmapBitsCapture.h"

BitBltGetBitmapBitsCapture::BitBltGetBitmapBitsCapture(HWND window)
{
	_window = window;
	RECT rect = {};
	GetClientRect(_window, &rect);
	_width = RectUtil::getRectWidth(rect);
	_height = RectUtil::getRectHeight(rect);
	createBuffer(_width, _height);
	_sourceContext = GetDC(window);
	_captureContext = CreateCompatibleDC(_sourceContext);
	_captureBitmap = CreateCompatibleBitmap(_sourceContext, _width, _height);
	SelectObject(_captureContext, _captureBitmap);
}

BitBltGetBitmapBitsCapture::~BitBltGetBitmapBitsCapture()
{
	ReleaseDC(_window, _sourceContext);
	DeleteDC(_captureContext);
	DeleteObject(_captureBitmap);
}

bool BitBltGetBitmapBitsCapture::getFrame()
{
	bool result = true;
	if (result)
	{
		result = BitBlt(_captureContext, 0, 0, _width, _height, _sourceContext, 0, 0, SRCCOPY);
	}
	if (result)
	{
		uint32_t* pixels = beginFrame();
		result = GetBitmapBits(_captureBitmap, _width * _height * 4, pixels);
		endFrame(result);
	}
	return result;
}
