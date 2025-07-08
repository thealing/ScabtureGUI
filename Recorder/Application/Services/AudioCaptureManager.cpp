#include "AudioCaptureManager.h"

AudioCaptureManager::AudioCaptureManager()
{
}

AudioCaptureManager::~AudioCaptureManager()
{
	if (_dispatcher != NULL)
	{
		_dispatcher->stop();
	}
}

const Event* AudioCaptureManager::getErrorEvent()
{
	return _errorEventPool.getEvent();
}

void AudioCaptureManager::setCapture(AudioCapture* capture)
{
	_lock.beginWriting();
	if (_dispatcher != NULL)
	{
		_dispatcher->stop();
		_dispatcher = NULL;
	}
	_capture = capture;
	if (_capture != NULL)
	{
		_dispatcher = new EventDispatcher();
		_dispatcher->addEntry(_capture->getErrorEvent(), BIND(AudioCaptureManager, onError, this));
		_dispatcher->start();
	}
	_lock.endWriting();
}

AudioCapture* AudioCaptureManager::lockCapture()
{
	_lock.beginReading();
	return _capture;
}

void AudioCaptureManager::unlockCapture()
{
	_lock.endReading();
}

void AudioCaptureManager::onError()
{
	_errorEventPool.setEvents();
}
