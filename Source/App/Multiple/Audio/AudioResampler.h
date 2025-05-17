#pragma once

class AudioResampler : public AudioCapture
{
public:

	AudioResampler(const AudioResamplerSettings& settings, AudioCapture* source);

	virtual ~AudioResampler();

	virtual HRESULT getFormat(IMFMediaType** format) override;

	virtual HRESULT getSample(IMFSample** sample) override;

private:

	void onFrame();

private:

	Status _status;
	UniquePointer<AudioCapture> _source;
	ComPointer<IMFMediaType> _inputType;
	ComPointer<IMFMediaType> _outputType;
	ComPointer<IMFTransform> _resampler;
	UINT32 _inputSampleRate;
	UINT32 _outputSampleRate;
};