#include "PrintWindowGetBitmapBitsCapture.h"

PrintWindowGetBitmapBitsCapture::PrintWindowGetBitmapBitsCapture(HWND window) : WindowCapture(window)
{
	SIZE size = WindowUtil::getClientSize(window);
	createBuffer(size.cx, size.cy);
	const Buffer* buffer = getBuffer();
	int height = buffer->getHeight();
	int stride = buffer->getStride();
	HDC sourceContext = GetDC(window); 
	_captureContext = CreateCompatibleDC(sourceContext);
	_captureBitmap = CreateCompatibleBitmap(sourceContext, stride, height);
	SelectObject(_captureContext, _captureBitmap);
	ReleaseDC(window, sourceContext);
}

PrintWindowGetBitmapBitsCapture::~PrintWindowGetBitmapBitsCapture()
{
	stop();
	DeleteDC(_captureContext);
	DeleteObject(_captureBitmap);
}

bool PrintWindowGetBitmapBitsCapture::captureFrame()
{
	const Buffer* buffer = getBuffer();
	int width = buffer->getWidth();
	int height = buffer->getHeight();
	int stride = buffer->getStride();
	bool result = true;
	if (result)
	{
		HWND window = getWindow();
		result = PrintWindow(window, _captureContext, PW_CLIENTONLY | PW_RENDERFULLCONTENT);
	}
	if (result)
	{
		uint32_t* pixels = beginFrame();
		result = GetBitmapBits(_captureBitmap, height * stride * sizeof(uint32_t), pixels);
		endFrame(result);
	}
	return result;
}
