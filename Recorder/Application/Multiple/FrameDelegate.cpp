#include "FrameDelegate.h"

template<class Base>
FrameDelegate<Base>::FrameDelegate(FrameSource* source)
{
	_source = source;
}

template<class Base>
const Event* FrameDelegate<Base>::getFrameEvent()
{
	return _source->getFrameEvent();
}

template<class Base>
const Event* FrameDelegate<Base>::getErrorEvent()
{
	return _source->getErrorEvent();
}

template<class Base>
void FrameDelegate<Base>::releaseFrameEvent(const Event* event)
{
	_source->releaseFrameEvent(event);
}

template<class Base>
void FrameDelegate<Base>::releaseErrorEvent(const Event* event)
{
	_source->releaseErrorEvent(event);
}
