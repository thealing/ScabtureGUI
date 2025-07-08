#pragma once

class AudioSettingsObserver : NonCopyable
{
public:

	AudioSettingsObserver(AudioSettingsManager* audioSettingsManager, AudioResamplerFactory* audioResamplerFactory, AudioEncoderFactory* audioEncoderFactory);

	~AudioSettingsObserver();

private:

	void onSettingsChanged();

	void updateAudioResamplerSettings(const AudioSettings& audioSettings);

	void updateAudioEncoderSettings(const AudioSettings& audioSettings);

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<AudioSettingsManager> _audioSettingsManager;
	WeakPointer<AudioResamplerFactory> _audioResamplerFactory;
	WeakPointer<AudioEncoderFactory> _audioEncoderFactory;
};

