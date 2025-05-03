#include "AudioResamplerFactory.h"

AudioResamplerFactory::AudioResamplerFactory() : _settings()
{
}

bool AudioResamplerFactory::setSettings(const AudioResamplerSettings& settings)
{
	if (MemoryUtil::areEqual(_settings, settings))
	{
		return false;
	}
	_settings = settings;
	_changeEventPool.setEvents();
	return true;
}

AudioResampler* AudioResamplerFactory::createResampler(AudioCapture* source) const
{
	return new AudioResampler(_settings, source);
}

const Event* AudioResamplerFactory::getChangeEvent() const
{
    return _changeEventPool.getEvent();
}
