#pragma once

class SilencePlayer : NonCopyable
{
public:

	SilencePlayer(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role);

	~SilencePlayer();

private:

	Status _status;
	ComPointer<IMMDevice> _device;
	ComPointer<IAudioClient> _audioClient;
	ComPointer<IAudioRenderClient> _renderClient;
};

