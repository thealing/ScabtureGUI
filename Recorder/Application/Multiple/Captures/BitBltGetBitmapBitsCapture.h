#pragma once

class BitBltGetBitmapBitsCapture : public WindowCapture
{
public:

	BitBltGetBitmapBitsCapture(HWND window, POINT position, SIZE size);

	~BitBltGetBitmapBitsCapture();

protected:
	
	virtual bool captureFrame() override;

private:

	POINT _position;
	HDC _sourceContext;
	HDC _captureContext;
	HBITMAP _captureBitmap;
};
