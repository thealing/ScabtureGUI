#pragma once

class BitBltCapture : public GdiCapture
{
protected:

	BitBltCapture(const CaptureSource& source);

	bool blit(DWORD flags);
};

