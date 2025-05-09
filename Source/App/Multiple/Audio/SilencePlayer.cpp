#include "SilencePlayer.h"

SilencePlayer::SilencePlayer(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role)
{
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
		_status = _audioClient->GetMixFormat(&_waveFormat);
	}
	if (_status)
	{
		DWORD flags = AUDCLNT_STREAMFLAGS_EVENTCALLBACK;
		_status = _audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, flags, 0, 0, _waveFormat, NULL);
	}
	if (_status)
	{
		_status = _audioClient->GetService(IID_PPV_ARGS(&_renderClient));
	}
	if (_status)
	{
		_status = _audioClient->SetEventHandle(_frameEvent);
	}
	if (_status)
	{
		Callback callback = BIND(SilencePlayer, onFrame, this);
		_eventDispather.addEntry(&_frameEvent, callback);
	}
	if (!_status)
	{
		LogUtil::logComWarning("SilencePlayer", _status);
	}
}

HRESULT SilencePlayer::start()
{
	Status result;
	if (_audioClient == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		_eventDispather.start();
		result = _audioClient->Start();
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

HRESULT SilencePlayer::stop()
{
	Status result;
	if (_audioClient == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = _audioClient->Stop();
		_eventDispather.stop();
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

void SilencePlayer::onFrame()
{
	Status result;
	UINT32 totalFrames = 0;
	UINT32 padding = 0;
	UINT32 framesAvailable = 0;
	BYTE* data = NULL;
	if (result)
	{
		result = _audioClient->GetBufferSize(&totalFrames);
	}
	if (result)
	{
		result = _audioClient->GetCurrentPadding(&padding);
	}
	if (result)
	{
		framesAvailable = totalFrames - padding;
		result = _renderClient->GetBuffer(framesAvailable, &data);
	}
	if (result)
	{
		result = _renderClient->ReleaseBuffer(framesAvailable, AUDCLNT_BUFFERFLAGS_SILENT);
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
}

