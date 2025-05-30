#include "SilencePlayer.h"

SilencePlayer::SilencePlayer(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role)
{
	WaveFormat waveFormat;
	if (enumerator == NULL)
	{
		_status = E_INVALIDARG;
	}
	if (_status)
	{
		_status = enumerator->GetDefaultAudioEndpoint(flow, role, &_device);
	}
	if (_status)
	{
		_status = _device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&_audioClient);
	}
	if (_status)
	{
		_status = _audioClient->GetMixFormat(&waveFormat);
	}
	if (_status)
	{
		DWORD flags = 0;
		_status = _audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, flags, 0, 0, waveFormat, NULL);
	}
	if (_status)
	{
		_status = _audioClient->GetService(IID_PPV_ARGS(&_renderClient));
	}
	if (_status)
	{
		_status = _audioClient->Start();
	}
	if (!_status)
	{
		LogUtil::logComWarning("SilencePlayer", _status);
	}
}

SilencePlayer::~SilencePlayer()
{
	if (_status)
	{
		_status = _audioClient->Stop();
	}
	if (!_status)
	{
		LogUtil::logComWarning("SilencePlayer", _status);
	}
}
