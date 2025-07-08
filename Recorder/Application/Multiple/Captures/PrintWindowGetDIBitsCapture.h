#pragma once

class PrintWindowGetDIBitsCapture : public WindowCapture
{
public:

	PrintWindowGetDIBitsCapture(HWND window);

	~PrintWindowGetDIBitsCapture();

protected:

	virtual bool captureFrame() override;

private:

	HDC _captureContext;
	HBITMAP _captureBitmap;
};

