#pragma once

class AudioVolumeMeter : NonCopyable
{
public:

	AudioVolumeMeter(AudioCapture* source);

	bool getVolumes(Volumes* volumes) const;

private:

	void update();

private:

	Status _status;
	int _channelCount;
	int _sampleSize;
	Volumes _volumes;
	UniquePointer<AudioCapture> _source;  // Must be the last field to be destructed first!
};

