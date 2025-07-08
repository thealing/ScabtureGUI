#pragma once

class AudioEncoder : public Encoder
{
public:

	AudioEncoder(const AudioEncoderSettings& settings, AudioCapture* source, SinkWriter* sinkWriter);

private:

	virtual HRESULT getSample(IMFSample** sample) override;

private:

	AudioEncoderSettings _settings;
	WeakPointer<AudioCapture> _source;
};

