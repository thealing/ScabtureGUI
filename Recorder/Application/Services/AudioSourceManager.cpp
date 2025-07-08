#include "AudioSourceManager.h"

#define AUDIO_SOURCE_SETTING_NAME L"Audio Source"

AudioSourceManager::AudioSourceManager()
{
	AudioSource source = AudioSourceNone;
	if (SaveUtil::loadSettings(AUDIO_SOURCE_SETTING_NAME, &source))
	{
		LogUtil::logInfo(L"AudioSourceManager: Loaded audio source %i.", source);
	}
	else
	{
		LogUtil::logWarning(L"AudioSourceManager: No saved audio source found.");
	}
	_source = source;
	_changeEventPool.setEvents();
}

const Event* AudioSourceManager::getChangeEvent()
{
	return _changeEventPool.getEvent();
}

void AudioSourceManager::setSource(AudioSource source)
{
	if (SaveUtil::saveSettings(AUDIO_SOURCE_SETTING_NAME, &source))
	{
		LogUtil::logInfo(L"AudioSourceManager: Saved audio source %i.", source);
	}
	else
	{
		LogUtil::logWarning(L"AudioSourceManager: Failed to save audio source %i.", source);
	}
	_source = source;
	_changeEventPool.setEvents();
}

AudioSource AudioSourceManager::getSource() const
{
	return _source;
}
