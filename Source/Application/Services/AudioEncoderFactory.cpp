#include "AudioEncoderFactory.h"

AudioEncoderFactory::AudioEncoderFactory()
{
}

bool AudioEncoderFactory::setSettings(const AudioEncoderSettings& settings)
{
	return _settingsManager.setSettings(settings);
}

Encoder* AudioEncoderFactory::createEncoder(AudioCapture* source, SinkWriter* sinkWriter) const
{
	AudioEncoderSettings settings = _settingsManager.getSettings();
	return new AudioEncoder(settings, source, sinkWriter);
}
