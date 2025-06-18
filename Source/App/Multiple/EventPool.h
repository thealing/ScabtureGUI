#pragma once

class EventPool : NonCopyable
{
public:

	EventPool();

	void setEvents();

	void resetEvents();

	const Event* getEvent();

	void deleteEvent(const Event* event);

private:

	ExclusiveLock _lock;
	UniqueStorage<Event> _events;
	bool _set;
};
