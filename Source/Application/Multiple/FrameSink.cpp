#include "FrameSink.h"

FrameSink::FrameSink(FrameSource* source)
{
	_source = source;
	if (_source != NULL)
	{
		_frameEvent = _source->getFrameEvent();
		_errorEvent = _source->getErrorEvent();
		_eventDispatcher.addEntry(_frameEvent, BIND(FrameSink, onFrame, this));
		_eventDispatcher.addEntry(_errorEvent, BIND(FrameSink, onError, this));
	}
}

FrameSink::~FrameSink()
{
	if (_source != NULL)
	{
		_source->releaseFrameEvent(_frameEvent);
		_source->releaseErrorEvent(_errorEvent);
	}
}

void FrameSink::start()
{
	_eventDispatcher.start();
}

void FrameSink::stop()
{
	_eventDispatcher.stop();
}
