#include "BitBltGetBitmapBitsCapture.h"

BitBltGetBitmapBitsCapture::BitBltGetBitmapBitsCapture(HWND window, POINT position, SIZE size) : WindowCapture(window)
{
	_position = position;
	createBuffer(size.cx, size.cy);
	const Buffer* buffer = getBuffer();
	int height = buffer->getHeight();
	int stride = buffer->getStride();
	_sourceContext = GetDC(window); 
	_captureContext = CreateCompatibleDC(_sourceContext);
	_captureBitmap = CreateCompatibleBitmap(_sourceContext, stride, height);
	SelectObject(_captureContext, _captureBitmap);
}

BitBltGetBitmapBitsCapture::~BitBltGetBitmapBitsCapture()
{
	stop();
	HWND window = getWindow();
	ReleaseDC(window, _sourceContext);
	DeleteDC(_captureContext);
	DeleteObject(_captureBitmap);
}

bool BitBltGetBitmapBitsCapture::captureFrame()
{
	const Buffer* buffer = getBuffer();
	int width = buffer->getWidth();
	int height = buffer->getHeight();
	int stride = buffer->getStride();
	bool result = true;
	if (result)
	{
		result = BitBlt(_captureContext, 0, 0, width, height, _sourceContext, _position.x, _position.y, SRCCOPY);
	}
	if (result)
	{
		uint32_t* pixels = beginFrame();
		result = GetBitmapBits(_captureBitmap, height * stride * sizeof(uint32_t), pixels);
		endFrame(result);
	}
	return result;
}
