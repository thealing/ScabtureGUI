#include "BaseEventDispatcher.h"

BaseEventDispatcher::BaseEventDispatcher()
{
	_events = new Event*[Capacity + 1];
	_count = 0;
	_events[0] = new Event();
}

BaseEventDispatcher::~BaseEventDispatcher()
{
	assert(_thread == NULL);
	delete _events[0];
	delete[] _events;
}

void BaseEventDispatcher::start()
{
	assert(_thread == NULL);
	_events[0]->reset();
	_thread = new Thread(BIND(BaseEventDispatcher, threadProc, this));
}

void BaseEventDispatcher::stop()
{
	assert(_thread != NULL);
	_events[0]->set();
	_thread = NULL;
}

int BaseEventDispatcher::getThreadId() const
{
	if (_thread == NULL)
	{
		return -1;
	}
	return _thread->getId();
}

int BaseEventDispatcher::addEntry(const Event* event)
{
	assert(_thread == NULL);
	assert(_count < Capacity);
	_count++;
	_events[_count] = (Event*)event;
	return _count - 1;
}

void BaseEventDispatcher::threadProc()
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
