#include "BitBltGetDIBitsCapture.h"

BitBltGetDIBitsCapture::BitBltGetDIBitsCapture(HWND window, POINT position, SIZE size) : WindowCapture(window)
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

BitBltGetDIBitsCapture::~BitBltGetDIBitsCapture()
{
	stop();
	HWND window = getWindow();
	ReleaseDC(window, _sourceContext);
	DeleteDC(_captureContext);
	DeleteObject(_captureBitmap);
}

bool BitBltGetDIBitsCapture::captureFrame()
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
		BITMAPINFO bitmapInfo = {};
		bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitmapInfo.bmiHeader.biWidth = stride;
		bitmapInfo.bmiHeader.biHeight = -height;
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biBitCount = 32;
		bitmapInfo.bmiHeader.biCompression = BI_RGB;
		uint32_t* pixels = beginFrame();
		result = GetDIBits(_captureContext, _captureBitmap, 0, height, pixels, &bitmapInfo, DIB_RGB_COLORS);
		endFrame(result);
	}
	return result;
}
