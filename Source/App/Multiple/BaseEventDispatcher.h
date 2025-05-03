#pragma once

class BaseEventDispatcher : NonCopyable
{
public:

	BaseEventDispatcher();

	virtual ~BaseEventDispatcher();

	void start();

	void stop();

	int getThreadId() const;

protected:

	int addEntry(const Event* event);

	virtual void onEvent(int index) = 0;

private:

	void threadProc();

protected:

	static const int Capacity = 16;

private:

	UniquePointer<Thread> _thread;
	Event** _events;
	int _count;
};

