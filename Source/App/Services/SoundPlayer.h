#pragma once

class SoundPlayer : NonCopyable
{
public:

	SoundPlayer();

	bool setSettings(const SoundSettings& settings);

	void playStartSound();

	void playStopSound();

	void playPauseSound();

	void playResumeSound();

private:

	SoundSettings _settings;
};

