#include "SoundPlayer.h"

SoundPlayer::SoundPlayer() : _settings()
{
}

bool SoundPlayer::setSettings(const SoundSettings& settings)
{
	if (MemoryUtil::areEqual(_settings, settings))
	{
		return false;
	}
	_settings = settings;
	return true;
}

void SoundPlayer::playStartSound()
{
	if (_settings.playStartSound)
	{
		Beep(5000, 150);
		Beep(5000, 150);
	}
}

void SoundPlayer::playStopSound()
{
	if (_settings.playStopSound)
	{
		Beep(2000, 150);
		Beep(2000, 150);
	}
}

void SoundPlayer::playPauseSound()
{
	if (_settings.playStartSound)
	{
		Beep(2000, 150);
	}
}

void SoundPlayer::playResumeSound()
{
	if (_settings.playStopSound)
	{
		Beep(5000, 150);
	}
}
