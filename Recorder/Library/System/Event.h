#pragma once

class Event : NonCopyable
{
public:

	static int waitOne(Event** events, int count);

	static int waitAll(Event** events, int count);

	static int wait(Event** events, int count, bool all);

	Event();

	~Event();

	void set();

	void reset();

	operator HANDLE() const;

private:

	HANDLE _handle;
};
