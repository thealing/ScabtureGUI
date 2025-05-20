#include "EventPool.h"

EventPool::EventPool()
{
}

void EventPool::setEvents() const
{
	int count = _events.getCount();
	for (int i = 0; i < count; i++)
	{
		Event* event = _events.getValue(i);
		if (event != NULL)
		{
			event->set();
		}
	}
}

void EventPool::resetEvents() const
{
	int count = _events.getCount();
	for (int i = 0; i < count; i++)
	{
		Event* event = _events.getValue(i);
		if (event != NULL)
		{
			event->reset();
		}
	}
}

const Event* EventPool::getEvent() const
{
	Event* event = new Event();
	event->set();
	_events.store(event);
	return event;
}

void EventPool::deleteEvent(const Event* event) const
{
	_events.dispose(event);
}
