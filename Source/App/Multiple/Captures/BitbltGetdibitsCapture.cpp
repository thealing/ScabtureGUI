#include "BitbltGetdibitsCapture.h"

BitBltGetDIBitsCapture::BitBltGetDIBitsCapture(const CaptureSource& source) : BitBltCapture(source)
{
}

bool BitBltGetDIBitsCapture::getFrame(Buffer* buffer)
{
	if (!blit(SRCCOPY))
	{
		return false;
	}
	void* pixels = buffer->beginWriting();
	int result = GetDIBits(_captureContext, _captureBitmap, 0, _source.height, pixels, &_bitmapInfo, DIB_RGB_COLORS);
	buffer->endWriting();
	return result != 0;
}
