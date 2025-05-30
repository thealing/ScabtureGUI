#include "FrameDelegate.h"

FrameDelegate::FrameDelegate(FrameSource* source)
{
	_source = source;
}

const Event* FrameDelegate::getFrameEvent()
{
	return _source->getFrameEvent();
}

const Event* FrameDelegate::getErrorEvent()
{
	return _source->getErrorEvent();
}

void FrameDelegate::releaseFrameEvent(const Event* event)
{
	_source->releaseFrameEvent(event);
}

void FrameDelegate::releaseErrorEvent(const Event* event)
{
	_source->releaseErrorEvent(event);
}
