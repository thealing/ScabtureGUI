#include "AudioVolumeMeter.h"

AudioVolumeMeter::AudioVolumeMeter(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role) : _volumes(), _format(AudioDataFormatUnknown)
{
	ComPointer<IMFMediaType> format;
	GUID subtype;
	UINT32 channels = 0;
	UINT32 bitsPerSample = 0;
	if (enumerator == NULL)
	{
		_status = E_INVALIDARG;
	}
	if (_status)
	{
		_source = new AudioDevice(enumerator, flow, role);
		_source->setCallback(BIND(AudioVolumeMeter, update, this));
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
		_status = format->GetUINT32(MF_MT_AUDIO_NUM_CHANNELS, &channels);
	}
	if (_status)
	{
		_status = format->GetUINT32(MF_MT_AUDIO_BITS_PER_SAMPLE, &bitsPerSample);
	}
	if (_status)
	{
		_sampleSize = bitsPerSample / 8;
		_channelCount = channels;
		if (subtype == MFAudioFormat_PCM && bitsPerSample == 8)
		{
			_format = AudioDataFormat8bit;
		}
		if (subtype == MFAudioFormat_PCM && bitsPerSample == 16)
		{
			_format = AudioDataFormat16bit;
		}
		if (subtype == MFAudioFormat_PCM && bitsPerSample == 32)
		{
			_format = AudioDataFormat32bit;
		}
		if (subtype == MFAudioFormat_Float && bitsPerSample == 32)
		{
			_format = AudioDataFormatFloat;
		}
		if (_format == AudioDataFormatUnknown)
		{
			_status = MF_E_UNSUPPORTED_FORMAT;
		}
	}
	if (!_status)
	{
		LogUtil::logComWarning("AudioVolumeMeter", _status);
	}
}

bool AudioVolumeMeter::getVolumes(Volumes* volumes) const
{
	*volumes = _volumes;
	return _status;
}

const Event* AudioVolumeMeter::getUpdateEvent() const
{
	return &_updateEvent;
}

void AudioVolumeMeter::update()
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
			switch (_format)
			{
				case AudioDataFormat8bit:
				{
					int8_t* samples = (int8_t*)data;
					for (int i = 0; i + _channelCount <= frameCount; i += _channelCount)
					{
						for (int j = 0; j < _channelCount; j++)
						{
							float value = abs(samples[i + j] - 128) / 128.0f;
							values[j] = max(values[j], value);
						}
					}
					break;
				}
				case AudioDataFormat16bit:
				{
					int16_t* samples = (int16_t*)data;
					for (int i = 0; i + _channelCount <= frameCount; i += _channelCount)
					{
						for (int j = 0; j < _channelCount; j++)
						{
							float value = abs(samples[i + j]) / 32768.0f;
							values[j] = max(values[j], value);
						}
					}
					break;
				}
				case AudioDataFormat32bit:
				{
					int32_t* samples = (int32_t*)data;
					for (int i = 0; i + _channelCount <= frameCount; i += _channelCount)
					{
						for (int j = 0; j < _channelCount; j++)
						{
							float value = abs(samples[i + j]) / 2147483648.0f;
							values[j] = max(values[j], value);
						}
					}
					break;
				}
				case AudioDataFormatFloat:
				{
					float* samples = (float*)data;
					for (int i = 0; i + _channelCount <= frameCount; i += _channelCount)
					{
						for (int j = 0; j < _channelCount; j++)
						{
							float value = fabsf(samples[i + j]);
							values[j] = max(values[j], value);
						}
					}
					break;
				}
			}
			if (_channelCount >= 1)
			{
				_volumes.left = values[0];
				_volumes.right = values[0];
			}
			if (_channelCount >= 2)
			{
				_volumes.left = values[0];
				_volumes.right = values[1];
			}
		}
		result = buffer->Unlock();
	}
	if (result)
	{
		_updateEvent.set();
	}
}
