#include "FrameSource.h"

FrameSource::FrameSource() : _events(), _used()
{
}

const Event* FrameSource::getFrameEvent()
{
	Event* event = NULL;
	for (int i = 0; i < Capacity; i++)
	{
		if (_used[i] == false)
		{
			_used[i] = true;
			event = &_events[i];
			break;
		}
	}
	assert(event != NULL);
	return event;
}

void FrameSource::releaseFrameEvent(const Event* event)
{
	intptr_t i = event - _events;
	assert(i >= 0);
	assert(i < Capacity);
	assert(_used[i] == true);
	_used[i] = false;
}

void FrameSource::signalFrame()
{
	for (int i = 0; i < Capacity; ++i)
	{
		if (_used[i] == true)
		{
			_events[i].set();
		}
	}
}
