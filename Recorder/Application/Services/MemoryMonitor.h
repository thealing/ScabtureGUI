#pragma once

class MemoryMonitor : NonCopyable
{
public:

	MemoryMonitor();

	void start();

	void stop();

	int getUsage() const;

	const Event* getUpdateEvent() const;

private:

	void update();

private:

	int _usage;
	Event _updateEvent;
	UniquePointer<Timer> _timer;
};
