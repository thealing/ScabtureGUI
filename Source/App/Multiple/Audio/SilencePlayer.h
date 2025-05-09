#pragma once

class SilencePlayer : NonCopyable
{
public:

	SilencePlayer(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role);

	HRESULT start();

	HRESULT stop();

private:

	void onFrame();

private:

	Status _status;
	ComPointer<IMMDevice> _device;
	ComPointer<IAudioClient> _audioClient;
	ComPointer<IAudioRenderClient> _renderClient;
	WaveFormat _waveFormat;
	EventDispatcher _eventDispather;
	Event _frameEvent;
};

