#pragma once

class CpuMonitor : NonCopyable
{
public:

	CpuMonitor();

	void start();

	void stop();

	int getUsage() const;

	const Event* getUpdateEvent() const;

private:

	void update();

private:

	int _usage;
	Event _updateEvent;
	uint64_t _previousTotalTime;
	uint64_t _previousUsedTime;
	UniquePointer<Timer> _timer;

private:

	static void getTimes(uint64_t* totalTime, uint64_t* usedTime);
};
