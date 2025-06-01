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

	const Event* getInputMeterErrorEvent() const;

	const Event* getOutputMeterErrorEvent() const;

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

