#pragma once

class EventPool : NonCopyable
{
public:

	EventPool();

	~EventPool();

	void setEvents();

	const Event* getEvent() const;

private:

	static const int Capacity = 4;

	Event* _events;
	mutable int _count;
};
