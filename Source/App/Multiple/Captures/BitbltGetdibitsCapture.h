#pragma once

class BitBltGetDIBitsCapture : public BitBltCapture
{
public:

	BitBltGetDIBitsCapture(const CaptureSource& source);

	virtual bool getFrame(Buffer* buffer) override;
};

