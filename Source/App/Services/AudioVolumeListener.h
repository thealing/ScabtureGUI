#pragma once

class AudioVolumeListener : NonCopyable
{
public:

	AudioVolumeListener();

	const Event* getUpdateEvent();

	const Event* getInputMeterErrorEvent();

	const Event* getOutputMeterErrorEvent();

	void setInputVolumeMeter(AudioVolumeMeter* meter);

	void setOutputVolumeMeter(AudioVolumeMeter* meter);

	bool getInputVolumes(Volumes* volumes) const;

	bool getOutputVolumes(Volumes* volumes) const;

private:

	void update();

private:

	static const int UpdateFps = 50;

	mutable ExclusiveLock _inputLock;
	mutable ExclusiveLock _outputLock;

	EventPool _updateEventPool;
	EventPool _inputMeterErrorEventPool;
	EventPool _outputMeterErrorEventPool;
	UniquePointer<AudioVolumeMeter> _inputMeter;
	UniquePointer<AudioVolumeMeter> _outputMeter;
	UniquePointer<Timer> _timer;
};

