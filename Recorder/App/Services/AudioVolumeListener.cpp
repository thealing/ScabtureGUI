#include "AudioVolumeListener.h"

AudioVolumeListener::AudioVolumeListener() : _inputVolumes(), _outputVolumes(), _inputWorking(true), _outputWorking(true)
{
	_timer = new Timer(0.1, 1.0 / UpdateFps, BIND(AudioVolumeListener, update, this));
}

void AudioVolumeListener::setInputVolumeMeter(AudioVolumeMeter* meter)
{
	ExclusiveLockHolder holder(&_inputLock);
	_inputMeter = meter;
	_inputVolumes = {};
	_inputWorking = false;
}

void AudioVolumeListener::setOutputVolumeMeter(AudioVolumeMeter* meter)
{
	ExclusiveLockHolder holder(&_outputLock);
	_outputMeter = meter;
	_outputVolumes = {};
	_outputWorking = false;
}

bool AudioVolumeListener::getInputVolumes(Volumes* volumes) const
{
	*volumes = _inputVolumes;
	return _inputWorking;
}

bool AudioVolumeListener::getOutputVolumes(Volumes* volumes) const
{
	*volumes = _outputVolumes;
	return _outputWorking;
}

const Event* AudioVolumeListener::getUpdateEvent() const
{
	return _updateEventPool.getEvent();
}

void AudioVolumeListener::update()
{
	updateInputVolumes();
	updateOutputVolumes();
	_updateEventPool.setEvents();
}

void AudioVolumeListener::updateInputVolumes()
{
	ExclusiveLockHolder holder(&_inputLock);
	if (_inputMeter != NULL)
	{
		HRESULT result = _inputMeter->getVolumes(&_inputVolumes);
		_inputWorking = SUCCEEDED(result);
	}
}

void AudioVolumeListener::updateOutputVolumes()
{
	ExclusiveLockHolder holder(&_outputLock);
	if (_outputMeter != NULL)
	{
		HRESULT result = _outputMeter->getVolumes(&_outputVolumes);
		_outputWorking = SUCCEEDED(result);
	}
}
