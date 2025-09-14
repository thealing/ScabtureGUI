#include "EventDispatcherBase.h"

EventDispatcherBase::EventDispatcherBase()
{
#ifdef FUZZ_TESTING
	delete _stopEvent._DEBUG_TIMER;
	_stopEvent._DEBUG_TIMER=NULL;
#endif
	_events = new const Event*[Capacity + 1];
	_count = 0;
	_events[0] = &_stopEvent;
}

EventDispatcherBase::~EventDispatcherBase()
{
	assert(_thread == NULL);
	delete[] _events;
}

void EventDispatcherBase::start()
{
	assert(_thread == NULL);
	_stopEvent.reset();
	_thread = new Thread(BIND(EventDispatcherBase, threadProc, this));
}

void EventDispatcherBase::stop()
{
	assert(_thread != NULL);
	_stopEvent.set();
	_thread = NULL;
}

int EventDispatcherBase::getThreadId() const
{
	if (_thread == NULL)
	{
		return -1;
	}
	return _thread->getId();
}

int EventDispatcherBase::addEntry(const Event* event)
{
	assert(_thread == NULL);
	assert(_count < Capacity);
	_count++;
	_events[_count] = event;
	return _count - 1;
}

void EventDispatcherBase::threadProc()
{
	while (true)
	{
		int index = Event::waitOne(_events, _count + 1);
		if (index < 0 || index > _count)
		{
			break;
		}
		if (index == 0)
		{
			break;
		}
		onEvent(index - 1);
	}
}
