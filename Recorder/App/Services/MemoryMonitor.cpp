#include "MemoryMonitor.h"

MemoryMonitor::MemoryMonitor() : _usage(0)
{
}

void MemoryMonitor::start()
{
	_timer = new Timer(0.05, 0.4, BIND(MemoryMonitor, update, this));
}

void MemoryMonitor::stop()
{
	_timer = NULL;
}

int MemoryMonitor::getUsage() const
{
	return _usage;
}

const Event* MemoryMonitor::getUpdateEvent() const
{
	return &_updateEvent;
}

void MemoryMonitor::update()
{
	HANDLE processHandle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS memoryCounters = {};
	GetProcessMemoryInfo(processHandle, &memoryCounters, sizeof(memoryCounters));
	_usage = (int)(memoryCounters.WorkingSetSize / 1000000);
	_updateEvent.set();
}
