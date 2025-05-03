#include "FpsCounter.h"

FpsCounter::FpsCounter()
{
	reset();
}

void FpsCounter::reset()
{
	WriteLockHolder holder(&_lock);
	_frameCounter = 0;
	_measuredFps = -1;
	_lastFrameTime = getTime();
	_lastMeasureTime = _lastFrameTime;
	_timer = new Timer(0.75, 1.0, BIND(FpsCounter, update, this));
}

void FpsCounter::recordFrame()
{
	WriteLockHolder holder(&_lock);
	_frameCounter++;
	_lastFrameTime = getTime();
}

int FpsCounter::getFps() const
{
	ReadLockHolder holder(&_lock);
	return _measuredFps;
}

const Event* FpsCounter::getUpdateEvent() const
{
	ReadLockHolder holder(&_lock);
	return _updateEventPool.getEvent();
}

void FpsCounter::update()
{
	WriteLockHolder holder(&_lock);
	double elapsedTime = _lastFrameTime - _lastMeasureTime;
	_measuredFps = lround(_frameCounter / elapsedTime);
	_frameCounter = 0;
	_lastMeasureTime = _lastFrameTime;
	_updateEventPool.setEvents();
}
