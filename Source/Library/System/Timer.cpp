#include "Timer.h"

double Timer::setResolution(double resolution)
{
	ULONG minResolution = 0;
	ULONG maxResolution = 0;
	ULONG currentResolution = 0;
	ntQueryTimerResolution(&minResolution, &maxResolution, &currentResolution);
	ULONG newResolution = (ULONG)(resolution * 10000000);
	newResolution = clamp(newResolution, maxResolution, minResolution);
	ntSetTimerResolution(newResolution, TRUE, &currentResolution);
	ntQueryTimerResolution(&minResolution, &maxResolution, &currentResolution);
	return currentResolution / 10000000.0;
}

Timer::Timer(double delay, double interval, const Callback& callback)
{
	_delay = (LONGLONG)(delay * 10000000);
	_interval = (LONGLONG)(interval * 10000000);
	_callback = callback;
	ntCreateTimer(&_timerHandle, TIMER_ALL_ACCESS, NULL, 0);
	_eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	_threadHandle = CreateThread(NULL, 0, threadProc, this, 0, NULL);
}

Timer::~Timer()
{
	SetEvent(_eventHandle);
	WaitForSingleObject(_threadHandle, INFINITE);
	CloseHandle(_threadHandle);
	CloseHandle(_eventHandle);
	ntClose(_timerHandle);
}

DWORD WINAPI Timer::threadProc(PVOID parameter)
{
	Timer* timer = (Timer*)parameter;
	LARGE_INTEGER dueTime;
	dueTime.QuadPart = getSystemTime();
	dueTime.QuadPart += timer->_delay;
	HANDLE objects[] = { timer->_eventHandle, timer->_timerHandle };
	while (true)
	{
		ntSetTimer(timer->_timerHandle, &dueTime, NULL, NULL, FALSE, 0, NULL);
		DWORD index = WaitForMultipleObjects(ARRAYSIZE(objects), objects, FALSE, INFINITE);
		if (index == WAIT_OBJECT_0)
		{
			break;
		}
		timer->_callback.invoke();
		if (timer->_interval == 0)
		{
			break;
		}
		dueTime.QuadPart = max(dueTime.QuadPart + timer->_interval, getSystemTime() - timer->_interval);
	}
	return 0;
}

LONGLONG Timer::getSystemTime()
{
	LARGE_INTEGER time = {};
	ntQuerySystemTime(&time);
	return time.QuadPart;
}

BOOL Timer::ntClose(HANDLE handle)
{
	static DynamicLibrary ntDll("ntdll.dll");
	static NtClose* function = ntDll.getFunction<NtClose>("NtClose");
	return function(handle);
}

BOOL Timer::ntCreateTimer(PHANDLE timerHandle, ACCESS_MASK desiredAccess, void* objectAttributes, DWORD timerType)
{
	static DynamicLibrary ntDll("ntdll.dll");
	static NtCreateTimer* function = ntDll.getFunction<NtCreateTimer>("NtCreateTimer");
	return function(timerHandle, desiredAccess, objectAttributes, timerType);
}

BOOL Timer::ntSetTimer(HANDLE timerHandle, PLARGE_INTEGER dueTime, PVOID timerApcRoutine, PVOID timerContext, BOOLEAN resume, LONG period, PBOOLEAN previousState)
{
	static DynamicLibrary ntDll("ntdll.dll");
	static NtSetTimer* function = ntDll.getFunction<NtSetTimer>("NtSetTimer");
	return function(timerHandle, dueTime, timerApcRoutine, timerContext, resume, period, previousState);
}

BOOL Timer::ntQuerySystemTime(PLARGE_INTEGER currentTime)
{
	static DynamicLibrary ntDll("ntdll.dll");
	static NtQuerySystemTime* function = ntDll.getFunction<NtQuerySystemTime>("NtQuerySystemTime");
	return function(currentTime);
}

BOOL Timer::ntQueryTimerResolution(PULONG minimumResolution, PULONG maximumResolution, PULONG currentResolution)
{
	static DynamicLibrary ntDll("ntdll.dll");
	static NtQueryTimerResolution* function = ntDll.getFunction<NtQueryTimerResolution>("NtQueryTimerResolution");
	return function(minimumResolution, maximumResolution, currentResolution);
}

BOOL Timer::ntSetTimerResolution(ULONG desiredResolution, BOOLEAN setResolution, PULONG currentResolution)
{
	static DynamicLibrary ntDll("ntdll.dll");
	static NtSetTimerResolution* function = ntDll.getFunction<NtSetTimerResolution>("NtSetTimerResolution");
	return function(desiredResolution, setResolution, currentResolution);
}
