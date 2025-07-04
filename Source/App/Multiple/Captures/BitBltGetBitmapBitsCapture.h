#pragma once

class BitBltGetBitmapBitsCapture : public BaseCapture
{
public:

	BitBltGetBitmapBitsCapture(HWND window);

	~BitBltGetBitmapBitsCapture();

	virtual bool getFrame() override;

private:

	HWND _window;
	int _width;
	int _height;
	HDC _sourceContext;
	HDC _captureContext;
	HBITMAP _captureBitmap;
};
