#pragma once

class PrintWindowGetBitmapBitsCapture : public WindowCapture
{
public:

	PrintWindowGetBitmapBitsCapture(HWND window);

	~PrintWindowGetBitmapBitsCapture();

protected:

	virtual bool captureFrame() override;

private:

	HDC _captureContext;
	HBITMAP _captureBitmap;
};

