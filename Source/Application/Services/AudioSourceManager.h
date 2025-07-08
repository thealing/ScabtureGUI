#pragma once

class AudioSourceManager : NonCopyable
{
public:

	AudioSourceManager();

	const Event* getChangeEvent();

	void setSource(AudioSource source);

	AudioSource getSource() const;

private:

	AudioSource _source;
	EventPool _changeEventPool;
};

