#include "AudioSourceManager.h"

#define AUDIO_SOURCE_SETTING_NAME L"Audio Source"

AudioSourceManager::AudioSourceManager() : SourceManager(AudioSourceNone)
{
	AudioSource source;
	bool loaded = SaveUtil::loadSettings(AUDIO_SOURCE_SETTING_NAME, &source);
	if (loaded)
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
	bool saved = SaveUtil::saveSettings(AUDIO_SOURCE_SETTING_NAME, &source);
	if (saved)
	{
		LogUtil::logInfo(L"AudioSourceManager: Saved audio source %i.", source);
	}
	else
	{
		LogUtil::logWarning(L"AudioSourceManager: Failed to save audio source %i.", source);
	}
	SourceManager::selectSource(source);
}
