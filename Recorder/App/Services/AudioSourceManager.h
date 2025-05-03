#pragma once

class AudioSourceManager : public SourceManager<AudioSource>
{
public:

	AudioSourceManager();

	void selectSource(AudioSource source);
};

