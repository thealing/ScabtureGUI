#pragma once

class AudioDevice : public AudioCapture
{
public:

	AudioDevice(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role);

	virtual ~AudioDevice();

	virtual HRESULT getFormat(IMFMediaType** format) override;

	virtual HRESULT getSample(IMFSample** sample) override;

	virtual HRESULT start() override;

	virtual HRESULT stop() override;

private:

	void onFrame();

private:

	Status _status;
	ComPointer<IMMDevice> _device;
	ComPointer<IAudioClient> _audioClient;
	ComPointer<IAudioCaptureClient> _captureClient;
	WaveFormat _waveFormat;
	UniquePointer<Timer> _timer;
};

