#pragma once

class AudioResamplerFactory : NonCopyable
{
public:

	AudioResamplerFactory();

	const Event* getChangeEvent();

	bool setSettings(const AudioResamplerSettings& settings);

	AudioResampler* createResampler(AudioCapture* source) const;

private:

	AsyncSettingsManager<AudioResamplerSettings> _settingsManager;
};

