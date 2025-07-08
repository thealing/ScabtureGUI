#pragma once

class BitBltDIBSectionCapture : public WindowCapture
{
public:

	BitBltDIBSectionCapture(HWND window, POINT position, SIZE size);

	~BitBltDIBSectionCapture();

protected:

	virtual bool captureFrame() override;

private:

	POINT _position;
	HDC _sourceContext;
	HDC _captureContext;
	HBITMAP _captureBitmap;
	void* _capturePixels;
};
