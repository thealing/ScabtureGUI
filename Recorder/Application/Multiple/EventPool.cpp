#include "EventPool.h"

EventPool::EventPool()
{
	_set = false;
}

void EventPool::setEvents()
{
	ExclusiveLockHolder holder(&_lock);
	for (Event* event : _events)
	{
		event->set();
	}
	_set = true;
}

void EventPool::resetEvents()
{
	ExclusiveLockHolder holder(&_lock);
	for (Event* event : _events)
	{
		event->reset();
	}
	_set = false;
}

const Event* EventPool::getEvent()
{
	ExclusiveLockHolder holder(&_lock);
	Event* event = new Event();
	if (_set)
	{
		event->set();
	}
	_events.store(event);
	return event;
}

void EventPool::deleteEvent(const Event* event)
{
	ExclusiveLockHolder holder(&_lock);
	_events.dispose(event);
}
