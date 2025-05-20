#include "FrameSource.h"

FrameSource::FrameSource()
{
}

const Event* FrameSource::getFrameEvent()
{
	return _frameEventPool.getEvent();
}

void FrameSource::releaseFrameEvent(const Event* event)
{
	_frameEventPool.deleteEvent(event);
}

void FrameSource::signalFrame()
{
	_frameEventPool.setEvents();
}
