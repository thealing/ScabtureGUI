#include "VideoCaptureManager.h"

VideoCaptureManager::VideoCaptureManager()
{
	_dispatcher = new EventDispatcher();
	_dispatcher->start();
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

const FpsCounter& VideoCaptureManager::getFpsCounter() const
{
	return _fpsCounter;
}

const Event* VideoCaptureManager::getChangeEvent() const
{
	return _changeEventPool.getEvent();
}

const Event* VideoCaptureManager::getFrameEvent() const
{
	return _frameEventPool.getEvent();
}

const Event* VideoCaptureManager::getErrorEvent() const
{
	return _errorEventPool.getEvent();
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
