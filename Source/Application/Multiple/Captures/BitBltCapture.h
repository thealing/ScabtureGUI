#pragma once

class BitBltCapture : public WindowCapture
{
public:

	BitBltCapture(HWND window, POINT position, SIZE size);

	~BitBltCapture();

protected:

	virtual bool captureFrame() override;

private:

	POINT _position;
	HDC _sourceContext;
	HDC _captureContext;
	HBITMAP _captureBitmap;
	void* _capturePixels;
};
