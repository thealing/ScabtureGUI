#pragma once

class AudioResamplerFactory : NonCopyable
{
public:

	AudioResamplerFactory();

	bool setSettings(const AudioResamplerSettings& settings);

	AudioResampler* createResampler(AudioCapture* source) const;

	const Event* getChangeEvent() const;

private:

	AudioResamplerSettings _settings;
	EventPool _changeEventPool;
};

