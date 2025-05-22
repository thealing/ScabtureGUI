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
	uint32_t* pixels = buffer->beginWriting();
	bool result = GetDIBits(_captureContext, _captureBitmap, 0, _source.height, pixels, &_bitmapInfo, DIB_RGB_COLORS);
	if (result)
	{
		int width = buffer->getWidth();
		int height = buffer->getHeight();
		int stride = buffer->getStride();
		drawOverlays(pixels, width, height, stride);
	}
	buffer->endWriting();
	return result;
}
