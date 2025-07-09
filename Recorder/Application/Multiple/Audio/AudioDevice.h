#pragma once

class AudioDevice : public FrameEmitter<AudioCapture>
{
public:

	AudioDevice(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role);

	virtual ~AudioDevice();

	virtual HRESULT getFormat(IMFMediaType** format) override;

	virtual HRESULT getSample(IMFSample** sample) override;

private:

	void onTimer();

private:

	ComPointer<IMMDevice> _device;
	ComPointer<IAudioClient> _audioClient;
	ComPointer<IAudioCaptureClient> _captureClient;
	WaveFormat _waveFormat;
	UniquePointer<Timer> _timer;
	UniquePointer<SilencePlayer> _player;
};

