#pragma once

class PrintWindowDIBSectionCapture : public WindowCapture
{
public:

	PrintWindowDIBSectionCapture(HWND window);

	~PrintWindowDIBSectionCapture();

protected:

	virtual bool captureFrame() override;

private:

	HDC _captureContext;
	HBITMAP _captureBitmap;
	void* _capturePixels;
};

