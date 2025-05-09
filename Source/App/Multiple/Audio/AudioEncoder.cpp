#include "AudioEncoder.h"

AudioEncoder::AudioEncoder(const AudioEncoderSettings& settings, AudioCapture* source, SinkWriter* sinkWriter) : Encoder(sinkWriter)
{
	_settings = settings;
	_source = source;
	ComPointer<IMFMediaType> inputType;
	ComPointer<IMFMediaType> outputType;
	UINT32 sampleRate = 0;
	UINT32 channels = 0;
	if (_source == NULL)
	{
		_status = E_INVALIDARG;
	}
	if (_status)
	{
		_status = _source->getFormat(&inputType);
	}
	if (_status)
	{
		_status = inputType->GetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, &sampleRate);
	}
	if (_status)
	{
		_status = inputType->GetUINT32(MF_MT_AUDIO_NUM_CHANNELS, &channels);
	}
	if (_status)
	{
		_status = MFCreateMediaType(&outputType);
	}
	if (_status)
	{
		_status = outputType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	}
	if (_status)
	{
		_status = outputType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_AAC);
	}
	if (_status)
	{
		_status = outputType->SetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE, 16);
	}
	if (_status)
	{
		_status = outputType->SetUINT32(MF_MT_AUDIO_AVG_BYTES_PER_SECOND, _settings.byteRate);
	}
	if (_status)
	{
		_status = outputType->SetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, sampleRate);
	}
	if (_status)
	{
		_status = outputType->SetUINT32(MF_MT_AUDIO_NUM_CHANNELS, channels);
	}
	if (_status)
	{
		_status = addStream(inputType, outputType);
	}
	if (_status)
	{
		addEvent(&_frameEvent);
		_source->setCallback(BIND(AudioEncoder, onFrame, this));
	}
	if (!_status)
	{
		LogUtil::logComError("AudioEncoder", _status);
	}
}

void AudioEncoder::onFrame()
{
	_frameEvent.set();
}

HRESULT AudioEncoder::doStart()
{
	if (_source == NULL)
	{
		return E_POINTER;
	}
	return _source->start();
}

HRESULT AudioEncoder::doStop()
{
	if (_source == NULL)
	{
		return E_POINTER;
	}
	return _source->stop();
}

HRESULT AudioEncoder::doPause()
{
	if (_source == NULL)
	{
		return E_POINTER;
	}
    return _source->stop();
}

HRESULT AudioEncoder::doResume()
{
	if (_source == NULL)
	{
		return E_POINTER;
	}
    return _source->start();
}

HRESULT AudioEncoder::getSample(IMFSample** sample)
{
	if (_source == NULL)
	{
		return E_POINTER;
	}
	return _source->getSample(sample);
}
