#include "AudioVolumeListener.h"

AudioVolumeListener::AudioVolumeListener()
{
	_timer = new Timer(0, 1.0 / UpdateFps, BIND(AudioVolumeListener, update, this));
}

void AudioVolumeListener::setInputVolumeMeter(AudioVolumeMeter* meter)
{
	ExclusiveLockHolder holder(&_inputLock);
	_inputMeter = meter;
}

void AudioVolumeListener::setOutputVolumeMeter(AudioVolumeMeter* meter)
{
	ExclusiveLockHolder holder(&_outputLock);
	_outputMeter = meter;
}

bool AudioVolumeListener::getInputVolumes(Volumes* volumes) const
{
	ExclusiveLockHolder holder(&_inputLock);
	if (_inputMeter != NULL)
	{
		return _inputMeter->getVolumes(volumes);
	}
	else
	{
		return false;
	}
}

bool AudioVolumeListener::getOutputVolumes(Volumes* volumes) const
{
	ExclusiveLockHolder holder(&_outputLock);
	if (_outputMeter != NULL)
	{
		return _outputMeter->getVolumes(volumes);
	}
	else
	{
		return false;
	}
}

const Event* AudioVolumeListener::getUpdateEvent() const
{
	return _updateEventPool.getEvent();
}

void AudioVolumeListener::update()
{
	_updateEventPool.setEvents();
}
