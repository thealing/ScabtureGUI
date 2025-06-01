#include "FrameEmitter.h"

template<class Base>
const Event* FrameEmitter<Base>::getFrameEvent()
{
	return _frameEventPool.getEvent();
}

template<class Base>
const Event* FrameEmitter<Base>::getErrorEvent()
{
	return _errorEventPool.getEvent();
}

template<class Base>
void FrameEmitter<Base>::releaseFrameEvent(const Event* event)
{
	_frameEventPool.deleteEvent(event);
}

template<class Base>
void FrameEmitter<Base>::releaseErrorEvent(const Event* event)
{
	_errorEventPool.deleteEvent(event);
}

template<class Base>
void FrameEmitter<Base>::signalFrame()
{
	_frameEventPool.setEvents();
}

template<class Base>
void FrameEmitter<Base>::signalError()
{
	_errorEventPool.setEvents();
}
