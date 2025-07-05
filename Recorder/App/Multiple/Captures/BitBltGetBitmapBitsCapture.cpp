#include "BitBltGetBitmapBitsCapture.h"

BitBltGetBitmapBitsCapture::BitBltGetBitmapBitsCapture(HWND window, RECT rect)
{
	_window = window;
	int width = RectUtil::getRectWidth(rect);
	int height = RectUtil::getRectHeight(rect);
	createBuffer(width, height);
	_position.x = rect.left;
	_position.y = rect.top;
	const Buffer* buffer = getBuffer();
	_size.x = buffer->getStride();
	_size.y = buffer->getHeight();
	_sourceContext = GetDC(window); 
	_captureContext = CreateCompatibleDC(_sourceContext);
	_captureBitmap = CreateCompatibleBitmap(_sourceContext, _size.x, _size.y);
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
		result = BitBlt(_captureContext, 0, 0, _size.x, _size.y, _sourceContext, _position.x, _position.y, SRCCOPY);
	}
	if (result)
	{
		uint32_t* pixels = beginFrame();
		result = GetBitmapBits(_captureBitmap, _size.x * _size.y * 4, pixels);
		endFrame(result);
	}
	if (!result)
	{
		setStatus(E_FAIL);
	}
	return result;
}
