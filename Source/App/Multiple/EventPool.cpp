#include "EventPool.h"

EventPool::EventPool()
{
	_events = new Event[Capacity];
	_count = 0;
}

EventPool::~EventPool()
{
	delete[] _events;
}

void EventPool::setEvents()
{
	for (int i = 0; i < Capacity; i++)
	{
		_events[i].set();
	}
}

const Event* EventPool::getEvent() const
{
	assert(_count < Capacity);
	_count++;
	return &_events[_count - 1];
}
