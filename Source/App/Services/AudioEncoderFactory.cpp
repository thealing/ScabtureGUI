#include "AudioEncoderFactory.h"

AudioEncoderFactory::AudioEncoderFactory() : _settings()
{
}

bool AudioEncoderFactory::setSettings(const AudioEncoderSettings& settings)
{
	if (MemoryUtil::areEqual(_settings, settings))
	{
		return false;
	}
	_settings = settings;
	return true;
}

Encoder* AudioEncoderFactory::createEncoder(AudioCapture* source, SinkWriter* sinkWriter) const
{
	return new AudioEncoder(_settings, source, sinkWriter);
}
