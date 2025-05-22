#pragma once

class GdiCapture : public Capture
{
public:

	GdiCapture(const CaptureSource& source);

	~GdiCapture();

protected:

	CaptureSource _source;
	BITMAPINFO _bitmapInfo;
	HDC _sourceContext;
	HDC _captureContext;
	HBITMAP _captureBitmap;
};

