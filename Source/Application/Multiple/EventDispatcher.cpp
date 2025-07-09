#include "EventDispatcher.h"

EventDispatcher::EventDispatcher()
{
	_callbacks = new Callback[Capacity];
}

EventDispatcher::~EventDispatcher()
{
	delete[] _callbacks;
}

void EventDispatcher::addEntry(const Event* event, const Callback& callback)
{
	int index = BaseEventDispatcher::addEntry(event);
	_callbacks[index] = callback;
}

void EventDispatcher::onEvent(int index)
{
	_callbacks[index].invoke();
}
