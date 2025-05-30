#pragma once

class AudioVolumeMeter : NonCopyable
{
public:

	AudioVolumeMeter(AudioCapture* source);

	~AudioVolumeMeter();

	bool getVolumes(Volumes* volumes) const;

	bool isInvalidated() const;

private:

	void onFrame();

	void onError();

private:

	Status _status;
	EventDispatcher _eventDispatcher;
	UniquePointer<AudioCapture> _source;
	int _channelCount;
	int _sampleSize;
	Volumes _volumes;
	bool _invalidated;
};

