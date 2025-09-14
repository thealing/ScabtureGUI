#pragma once

class EventDispatcherBase : Virtual
{
public:

	EventDispatcherBase();

	~EventDispatcherBase();

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
	Event _stopEvent;
	const Event** _events;
	int _count;
};

