#include "FrameEmitter.h"

const Event* FrameEmitter::getFrameEvent()
{
	return _frameEventPool.getEvent();
}

const Event* FrameEmitter::getErrorEvent()
{
	return _errorEventPool.getEvent();
}

void FrameEmitter::releaseFrameEvent(const Event* event)
{
	_frameEventPool.deleteEvent(event);
}

void FrameEmitter::releaseErrorEvent(const Event* event)
{
	_errorEventPool.deleteEvent(event);
}

void FrameEmitter::signalFrame()
{
	_frameEventPool.setEvents();
}

void FrameEmitter::signalError()
{
	_errorEventPool.setEvents();
}
