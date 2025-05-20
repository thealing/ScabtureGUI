#include "AudioResamplerFactory.h"

AudioResamplerFactory::AudioResamplerFactory()
{
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

const Event* AudioResamplerFactory::getChangeEvent() const
{
	return _settingsManager.getChangeEvent();
}
