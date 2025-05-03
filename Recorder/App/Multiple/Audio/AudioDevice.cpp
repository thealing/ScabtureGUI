#include "AudioDevice.h"

AudioDevice::AudioDevice(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role)
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
		if (flow == eRender)
		{
			flags |= AUDCLNT_STREAMFLAGS_LOOPBACK;
		}
		_status = _audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, flags, 0, 0, _waveFormat, NULL);
	}
	if (_status)
	{
		_status = _audioClient->GetService(IID_PPV_ARGS(&_captureClient));
	}
	if (_status)
	{
		_status = _audioClient->SetEventHandle(_frameEvent);
	}
	if (_status)
	{
		_eventDispather.addEntry(&_frameEvent, BIND(AudioDevice, onFrame, this));
	}
	if (!_status)
	{
		LogUtil::logComWarning("AudioDevice", _status);
	}
}

AudioDevice::~AudioDevice()
{
}

HRESULT AudioDevice::getFormat(IMFMediaType** format)
{
	Status result;
	if (_waveFormat == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = MFCreateMediaType(format);
	}
	if (result)
	{
		result = MFInitMediaTypeFromWaveFormatEx(*format, _waveFormat, _waveFormat.getSize());
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

HRESULT AudioDevice::getSample(IMFSample** sample)
{
	Status result;
	ComPointer<IMFMediaBuffer> buffer;
	BYTE* frameBuffer = NULL;
	UINT32 frameCount = 0;
	DWORD flags = 0;
	UINT32 bufferSize = 0;
	BYTE* bufferData = NULL;
	if (_captureClient == NULL)
	{
		result = E_POINTER;
	}
	if (_waveFormat == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = _captureClient->GetBuffer(&frameBuffer, &frameCount, &flags, NULL, NULL);
	}
	if (result)
	{
		bufferSize = frameCount * _waveFormat->nBlockAlign;
		result = MFCreateMemoryBuffer(bufferSize, &buffer);
	}
	if (result)
	{
		result = buffer->SetCurrentLength(bufferSize);
	}
	if (result)
	{
		result = buffer->Lock(&bufferData, NULL, NULL);
	}
	if (result)
	{
		memcpy(bufferData, frameBuffer, bufferSize);
		result = buffer->Unlock();
	}
	if (frameBuffer != NULL)
	{
		_captureClient->ReleaseBuffer(frameCount);
	}
	if (result)
	{
		result = MFCreateSample(sample);
	}
	if (result)
	{
		result = (*sample)->AddBuffer(buffer);
	}
	if (result)
	{
		LONGLONG duration = llround(10000000.0 * frameCount / _waveFormat->nSamplesPerSec); 
		result = (*sample)->SetSampleDuration(duration);
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

HRESULT AudioDevice::start()
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

HRESULT AudioDevice::stop()
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

void AudioDevice::onFrame()
{
	invokeCallback();
}
