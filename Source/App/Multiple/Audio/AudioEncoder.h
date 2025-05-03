#pragma once

class AudioEncoder : public Encoder
{
public:

	AudioEncoder(const AudioEncoderSettings& settings, AudioCapture* source, SinkWriter* sinkWriter);

private:

	void onFrame();

	virtual HRESULT doStart() override;

	virtual HRESULT doStop() override;

	virtual HRESULT getSample(IMFSample** sample) override;

private:

	Status _status;
	AudioEncoderSettings _settings;
	WeakPointer<AudioCapture> _source;
	Event _frameEvent;
};

