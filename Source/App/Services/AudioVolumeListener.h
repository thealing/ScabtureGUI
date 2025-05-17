#pragma once

class AudioVolumeListener : NonCopyable
{
public:

	AudioVolumeListener();

	void setInputVolumeMeter(AudioVolumeMeter* meter);

	void setOutputVolumeMeter(AudioVolumeMeter* meter);

	bool getInputVolumes(Volumes* volumes) const;

	bool getOutputVolumes(Volumes* volumes) const;

	const Event* getUpdateEvent() const;

private:

	void update();

private:

	static const int UpdateFps = 50;

	mutable ExclusiveLock _inputLock;
	mutable ExclusiveLock _outputLock;

	UniquePointer<AudioVolumeMeter> _inputMeter;
	UniquePointer<AudioVolumeMeter> _outputMeter;
	UniquePointer<Timer> _timer;
	EventPool _updateEventPool;
};

