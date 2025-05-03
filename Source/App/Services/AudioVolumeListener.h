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

	void updateInputVolumes();

	void updateOutputVolumes();

private:

	static const int UpdateFps = 50;

	mutable ExclusiveLock _inputLock;
	mutable ExclusiveLock _outputLock;

	UniquePointer<AudioVolumeMeter> _inputMeter;
	UniquePointer<AudioVolumeMeter> _outputMeter;
	Volumes _inputVolumes;
	Volumes _outputVolumes;
	bool _inputWorking;
	bool _outputWorking;
	UniquePointer<Timer> _timer;
	EventPool _updateEventPool;
};

