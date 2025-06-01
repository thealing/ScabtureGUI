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

#ifdef FUZZ_TESTING
public:
	Timer* _DEBUG_TIMER;

	void _DEBUG_TIMER_PROC(){
		if (rand() % 10 == 0) {
			SetEvent(_handle);
		}
	}
#endif
};
