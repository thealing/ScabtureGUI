#include "CpuMonitor.h"

CpuMonitor::CpuMonitor()
{
	_usage = 0;
	_previousTotalTime = 0;
	_previousUsedTime = 0;
}

void CpuMonitor::start()
{
	getTimes(&_previousTotalTime, &_previousUsedTime);
	_timer = new Timer(0.1, 0.75, BIND(CpuMonitor, update, this));
}

void CpuMonitor::stop()
{
	_timer = NULL;
}

int CpuMonitor::getUsage() const
{
	return _usage;
}

const Event* CpuMonitor::getUpdateEvent() const
{
	return &_updateEvent;
}

void CpuMonitor::update()
{
	uint64_t currentTotalTime;
	uint64_t currentUsedTime;
	getTimes(&currentTotalTime, &currentUsedTime);
	_usage = (int)(100 * (currentUsedTime - _previousUsedTime) / max(currentTotalTime - _previousTotalTime, 1ull));
	_previousTotalTime = currentTotalTime;
	_previousUsedTime = currentUsedTime;
	_updateEvent.set();
}

void CpuMonitor::getTimes(uint64_t* totalTime, uint64_t* usedTime)
{
	uint64_t systemIdleTime = 0;
	uint64_t systemKernelTime = 0;
	uint64_t systemUserTime = 0;
	GetSystemTimes((LPFILETIME)&systemIdleTime, (LPFILETIME)&systemKernelTime, (LPFILETIME)&systemUserTime);
	HANDLE processHandle = GetCurrentProcess();
	uint64_t processCreationTime = 0;
	uint64_t processExitTime = 0;
	uint64_t processKernelTime = 0;
	uint64_t processUserTime = 0;
	GetProcessTimes(processHandle, (LPFILETIME)&processCreationTime, (LPFILETIME)&processExitTime, (LPFILETIME)&processKernelTime, (LPFILETIME)&processUserTime);
	*totalTime = systemKernelTime + systemUserTime;
	*usedTime = processKernelTime + processUserTime;
}
