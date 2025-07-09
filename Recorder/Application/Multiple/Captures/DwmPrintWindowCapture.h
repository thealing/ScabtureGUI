#pragma once

class DwmPrintWindowCapture : public WindowCapture
{
public:

	DwmPrintWindowCapture(HWND window);

	~DwmPrintWindowCapture();

protected:

	virtual bool captureFrame() override;

private:

	HDC _captureContext;
	HBITMAP _captureBitmap;
	void* _capturePixels;
};

