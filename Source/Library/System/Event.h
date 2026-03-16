#pragma once

class Event : NonCopyable
{
public:

	static int waitOne(const Event** events, int count);

	static int waitAll(const Event** events, int count);

	static int wait(const Event** events, int count, bool all);

	Event();

	~Event();

	void set();

	void reset();

private:

	HANDLE _handle;
};
