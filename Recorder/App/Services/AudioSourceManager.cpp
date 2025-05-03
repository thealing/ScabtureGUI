#include "AudioSourceManager.h"

#define AUDIO_SOURCE_SETTING_NAME L"Audio Source"

AudioSourceManager::AudioSourceManager() : SourceManager(AudioSourceNone)
{
	SettingsProvider<AudioSource> provider;
	AudioSource source;
	if (provider.load(AUDIO_SOURCE_SETTING_NAME, &source))
	{
		LogUtil::logInfo(L"AudioSourceManager: Loaded audio source %i.", source);
		SourceManager::selectSource(source);
	}
	else
	{
		LogUtil::logWarning(L"AudioSourceManager: No saved audio source found.");
	}
}

void AudioSourceManager::selectSource(AudioSource source)
{
	SettingsProvider<AudioSource> provider;
	if (provider.save(AUDIO_SOURCE_SETTING_NAME, &source))
	{
		LogUtil::logInfo(L"AudioSourceManager: Saved audio source %i.", source);
	}
	else
	{
		LogUtil::logWarning(L"AudioSourceManager: Failed to save audio source %i.", source);
	}
	SourceManager::selectSource(source);
}
