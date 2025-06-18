#include "VideoCaptureManager.h"

VideoCaptureManager::VideoCaptureManager()
{
}

VideoCaptureManager::~VideoCaptureManager()
{
	if (_dispatcher != NULL)
	{
		_dispatcher->stop();
	}
}

void VideoCaptureManager::reset()
{
	_lock.beginWriting();
	if (_dispatcher != NULL)
	{
		_dispatcher->stop();
		_dispatcher = NULL;
	}
	_capture = NULL;
	_lock.endWriting();
}

void VideoCaptureManager::setCapture(VideoCapture* capture)
{
	_lock.beginWriting();
	_capture = capture;
	_dispatcher = new EventDispatcher();
	_dispatcher->addEntry(_capture->getFrameEvent(), BIND(VideoCaptureManager, onFrame, this));
	_dispatcher->addEntry(_capture->getErrorEvent(), BIND(VideoCaptureManager, onError, this));
	_dispatcher->start();
	_lock.endWriting();
	_changeEventPool.setEvents();
}

VideoCapture* VideoCaptureManager::lockCapture()
{
	_lock.beginReading();
	return _capture;
}

void VideoCaptureManager::unlockCapture()
{
	_lock.endReading();
}

const Event* VideoCaptureManager::getChangeEvent()
{
	return _changeEventPool.getEvent();
}

const Event* VideoCaptureManager::getFrameEvent()
{
	return _frameEventPool.getEvent();
}

const Event* VideoCaptureManager::getErrorEvent()
{
	return _errorEventPool.getEvent();
}

const FpsCounter& VideoCaptureManager::getFpsCounter() const
{
	return _fpsCounter;
}

void VideoCaptureManager::onFrame()
{
	_fpsCounter.recordFrame();
	_frameEventPool.setEvents();
}

void VideoCaptureManager::onError()
{
	_errorEventPool.setEvents();
}
