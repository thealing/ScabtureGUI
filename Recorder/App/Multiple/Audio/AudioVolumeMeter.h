#pragma once

class AudioVolumeMeter : NonCopyable
{
public:

	AudioVolumeMeter(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role);

	bool getVolumes(Volumes* volumes) const;

	const Event* getUpdateEvent() const;

private:

	void update();

private:

	Status _status;
	UniquePointer<AudioCapture> _source;
	int _channelCount;
	int _sampleSize;
	AudioDataFormat _format;
	Volumes _volumes;
	Event _updateEvent;
};

