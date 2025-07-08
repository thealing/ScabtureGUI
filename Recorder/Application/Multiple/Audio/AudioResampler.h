#pragma once

class AudioResampler : public FrameDelegate<AudioCapture>
{
public:

	AudioResampler(const AudioResamplerSettings& settings, AudioCapture* source);

	virtual HRESULT getFormat(IMFMediaType** format) override;

	virtual HRESULT getSample(IMFSample** sample) override;

private:

	Status _status;
	ComPointer<IMFMediaType> _inputType;
	ComPointer<IMFMediaType> _outputType;
	ComPointer<IMFTransform> _resampler;
	UniquePointer<AudioCapture> _source;
	UINT32 _inputSampleRate;
	UINT32 _outputSampleRate;
};