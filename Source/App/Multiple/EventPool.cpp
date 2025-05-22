#include "EventPool.h"

EventPool::EventPool()
{
}

void EventPool::setEvents() const
{
	for (Event* event : _events)
	{
		event->set();
	}
}

void EventPool::resetEvents() const
{
	for (Event* event : _events)
	{
		event->reset();
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
