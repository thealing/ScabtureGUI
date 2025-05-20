#pragma once

class EventPool : NonCopyable
{
public:

	EventPool();

	void setEvents() const;

	void resetEvents() const;

	const Event* getEvent() const;

	void deleteEvent(const Event* event) const;

private:

	mutable UniqueStorage<Event> _events;
};
