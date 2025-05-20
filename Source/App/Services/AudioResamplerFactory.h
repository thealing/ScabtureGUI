#pragma once

class AudioResamplerFactory : NonCopyable
{
public:

	AudioResamplerFactory();

	bool setSettings(const AudioResamplerSettings& settings);

	AudioResampler* createResampler(AudioCapture* source) const;

	const Event* getChangeEvent() const;

private:

	AsyncSettingsManager<AudioResamplerSettings> _settingsManager;
};

