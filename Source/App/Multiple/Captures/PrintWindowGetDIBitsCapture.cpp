#include "PrintWindowGetDIBitsCapture.h"

PrintWindowGetDIBitsCapture::PrintWindowGetDIBitsCapture(HWND window) : WindowCapture(window)
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

PrintWindowGetDIBitsCapture::~PrintWindowGetDIBitsCapture()
{
	stop();
	DeleteDC(_captureContext);
	DeleteObject(_captureBitmap);
}

bool PrintWindowGetDIBitsCapture::captureFrame()
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
