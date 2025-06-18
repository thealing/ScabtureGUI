#include "AudioVolumeListener.h"

AudioVolumeListener::AudioVolumeListener()
{
	_timer = new Timer(0, 1.0 / UpdateFps, BIND(AudioVolumeListener, update, this));
}

const Event* AudioVolumeListener::getUpdateEvent()
{
	return _updateEventPool.getEvent();
}

const Event* AudioVolumeListener::getInputMeterErrorEvent()
{
	return _inputMeterErrorEventPool.getEvent();
}

const Event* AudioVolumeListener::getOutputMeterErrorEvent()
{
	return _outputMeterErrorEventPool.getEvent();
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

void AudioVolumeListener::update()
{
	ExclusiveLockHolder inputHolder(&_inputLock);
	ExclusiveLockHolder outputHolder(&_outputLock);
	if (_inputMeter != NULL || _outputMeter != NULL)
	{
		_updateEventPool.setEvents();
	}
	if (_inputMeter != NULL && _inputMeter->isFailed())
	{
		_inputMeterErrorEventPool.setEvents();
	}
	if (_outputMeter != NULL && _outputMeter->isFailed())
	{
		_outputMeterErrorEventPool.setEvents();
	}
}
