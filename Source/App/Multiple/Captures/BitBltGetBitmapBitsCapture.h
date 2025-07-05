#pragma once

class BitBltGetBitmapBitsCapture : public BaseCapture
{
public:

	BitBltGetBitmapBitsCapture(HWND window, RECT rect);

	~BitBltGetBitmapBitsCapture();

	virtual bool getFrame() override;

private:

	HWND _window;
	Vector _position;
	Vector _size;
	HDC _sourceContext;
	HDC _captureContext;
	HBITMAP _captureBitmap;
};
