#include "AudioResamplerFactory.h"

AudioResamplerFactory::AudioResamplerFactory()
{
}

const Event* AudioResamplerFactory::getChangeEvent()
{
	return _settingsManager.getChangeEvent();
}

bool AudioResamplerFactory::setSettings(const AudioResamplerSettings& settings)
{
	return _settingsManager.setSettings(settings);
}

AudioResampler* AudioResamplerFactory::createResampler(AudioCapture* source) const
{
	AudioResamplerSettings settings = _settingsManager.getSettings();
	return new AudioResampler(settings, source);
}
