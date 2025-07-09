#pragma once

class BaseEventDispatcher : NonCopyable
{
public:

	static const int Capacity = 16;

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

private:

	UniquePointer<Thread> _thread;
	Event _stopEvent;
	const Event** _events;
	int _count;
};

