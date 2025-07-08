#pragma once

class AudioCapture : public FrameSource
{
public:

	virtual ~AudioCapture();

	virtual HRESULT getFormat(IMFMediaType** format) = 0;

	virtual HRESULT getSample(IMFSample** sample) = 0;
};

