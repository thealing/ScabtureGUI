#include "BitbltCapture.h"

BitBltCapture::BitBltCapture(const CaptureSource& source) : GdiCapture(source)
{
}

bool BitBltCapture::blit(DWORD flags)
{
	BOOL result = BitBlt(_captureContext, 0, 0, _source.width, _source.height, _sourceContext, _source.rect.left, _source.rect.top, flags);
	return result != 0;
}
