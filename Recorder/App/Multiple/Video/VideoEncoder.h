#pragma once

class VideoEncoder : public Encoder
{
public:

	VideoEncoder(const VideoEncoderSettings& settings, VideoCapture* source, SinkWriter* sinkWriter);

private:

	virtual HRESULT getSample(IMFSample** sample) override;

private:

	VideoEncoderSettings _settings;
	WeakPointer<VideoCapture> _source;
};

