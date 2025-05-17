#pragma once

class MediaSource : NonCopyable
{
public:

	virtual ~MediaSource();

	virtual HRESULT getFormat(IMFMediaType** format) = 0;

	virtual HRESULT getSample(IMFSample** sample) = 0;
};

