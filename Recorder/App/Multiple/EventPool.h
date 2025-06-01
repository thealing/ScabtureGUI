#pragma once

class EventPool : NonCopyable
{
public:

	EventPool();

	void setEvents();

	void resetEvents();

	const Event* getEvent() const;

	void deleteEvent(const Event* event) const;

private:

	mutable ExclusiveLock _lock;
	mutable UniqueStorage<Event> _events;

	bool _set;
};
