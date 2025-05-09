#pragma once

class VideoEncoder : public Encoder
{
public:

	VideoEncoder(const VideoEncoderSettings& settings, VideoCapture* source, SinkWriter* sinkWriter);

	~VideoEncoder();

private:

	virtual HRESULT getSample(IMFSample** sample) override;

private:

	Status _status;
	VideoEncoderSettings _settings;
	WeakPointer<VideoCapture> _source;
	WeakPointer<const Event> _frameEvent;
};

