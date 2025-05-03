#include "FrameSource.h"

const Event* FrameSource::getFrameEvent() const
{
	return _frameEventPool.getEvent();
}

void FrameSource::signalFrame()
{
	_frameEventPool.setEvents();
}
