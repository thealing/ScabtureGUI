#include "EventPool.h"

EventPool::EventPool()
{
	_set = false;
}

void EventPool::setEvents()
{
	for (Event* event : _events)
	{
		event->set();
	}
	_set = true;
}

void EventPool::resetEvents()
{
	for (Event* event : _events)
	{
		event->reset();
	}
	_set = false;
}

const Event* EventPool::getEvent() const
{
	Event* event = new Event();
	if (_set)
	{
		event->set();
	}
	_events.store(event);
	return event;
}

void EventPool::deleteEvent(const Event* event) const
{
	_events.dispose(event);
}
