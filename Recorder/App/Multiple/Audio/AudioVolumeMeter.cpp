#include "AudioVolumeMeter.h"

AudioVolumeMeter::AudioVolumeMeter(AudioCapture* source)
{
	_source = source;
	_sampleSize = 0;
	_channelCount = 0;
	_volumes = {};
	_failed = false;
	ComPointer<IMFMediaType> format;
	GUID subtype;
	UINT32 numChannels = 0;
	UINT32 bitsPerSample = 0;
	if (_source == NULL)
	{
		_status = E_INVALIDARG;
	}
	if (_status)
	{
		_status = _source->getFormat(&format);
	}
	if (_status)
	{
		_status = format->GetGUID(MF_MT_SUBTYPE, &subtype);
	}
	if (_status)
	{
		_status = format->GetUINT32(MF_MT_AUDIO_NUM_CHANNELS, &numChannels);
	}
	if (_status)
	{
		_status = format->GetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE, &bitsPerSample);
	}
	if (_status)
	{
		if (subtype == MFAudioFormat_PCM && bitsPerSample == 16)
		{
			_sampleSize = bitsPerSample / 8;
			_channelCount = numChannels;
		}
		else
		{
			_status = MF_E_UNSUPPORTED_FORMAT;
		}
	}
	if (_status)
	{
		_eventDispatcher.addEntry(_source->getFrameEvent(), BIND(AudioVolumeMeter, onFrame, this));
		_eventDispatcher.addEntry(_source->getErrorEvent(), BIND(AudioVolumeMeter, onError, this));
		_eventDispatcher.start();
	}
	if (!_status)
	{
		LogUtil::logComWarning("AudioVolumeMeter", _status);
	}
}

AudioVolumeMeter::~AudioVolumeMeter()
{
	if (_status)
	{
		_eventDispatcher.stop();
	}
}

bool AudioVolumeMeter::getVolumes(Volumes* volumes) const
{
	*volumes = _volumes;
	return _status;
}

bool AudioVolumeMeter::isFailed() const
{
	return _failed;
}

void AudioVolumeMeter::onFrame()
{
	Status result;
	ComPointer<IMFSample> sample;
	ComPointer<IMFMediaBuffer> buffer;
	BYTE* data = NULL;
	DWORD length = 0;
	if (result)
	{
		result = _status;
	}
	if (result)
	{
		result = _source->getSample(&sample);
	}
	if (result)
	{
		result = sample->ConvertToContiguousBuffer(&buffer);
	}
	if (result)
	{
		result = buffer->Lock(&data, NULL, &length);
	}
	if (result)
	{
		if (length > 0 && _sampleSize > 0 && _channelCount > 0)
		{
			int frameCount = length / _sampleSize;
			float* values = new float[_channelCount];
			for (int i = 0; i < _channelCount; i++)
			{
				values[i] = 0;
			}
			int16_t* samples = (int16_t*)data;
			for (int i = 0; i + _channelCount <= frameCount; i += _channelCount)
			{
				for (int j = 0; j < _channelCount; j++)
				{
					float value = abs(samples[i + j]) / 32768.0f;
					values[j] = max(values[j], value);
				}
			}
			Volumes newVolumes = {};
			if (_channelCount >= 1)
			{
				newVolumes.left = values[0];
				newVolumes.right = values[0];
			}
			if (_channelCount >= 2)
			{
				newVolumes.left = values[0];
				newVolumes.right = values[1];
			}
			delete[] values;
			_volumes.left = (_volumes.left + newVolumes.left) / 2;
			_volumes.right = (_volumes.right + newVolumes.right) / 2;
		}
		else
		{
			_volumes.left = 0;
			_volumes.right = 0;
		}
		result = buffer->Unlock();
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
}

void AudioVolumeMeter::onError()
{
	_failed = true;
}
