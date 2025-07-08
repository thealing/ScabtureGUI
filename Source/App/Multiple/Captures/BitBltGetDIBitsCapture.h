#pragma once

class BitBltGetDIBitsCapture : public WindowCapture
{
public:

	BitBltGetDIBitsCapture(HWND window, POINT position, SIZE size);

	~BitBltGetDIBitsCapture();

protected:

	virtual bool captureFrame() override;

private:

	POINT _position;
	HDC _sourceContext;
	HDC _captureContext;
	HBITMAP _captureBitmap;
};
