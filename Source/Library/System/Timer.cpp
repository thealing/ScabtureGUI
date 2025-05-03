#include "Timer.h"

typedef NTSTATUS (NTAPI* NtQueryTimerResolution)(PULONG, PULONG, PULONG);
typedef NTSTATUS (NTAPI* NtSetTimerResolution)(ULONG, BOOLEAN, PULONG);
typedef NTSTATUS (NTAPI* NtCreateTimer)(PHANDLE, ACCESS_MASK, void*, DWORD);
typedef NTSTATUS (NTAPI* NtSetTimer)(HANDLE, PLARGE_INTEGER, PVOID, PVOID, BOOLEAN, LONG, PBOOLEAN);
typedef NTSTATUS (NTAPI* NtClose)(HANDLE);
typedef NTSTATUS (NTAPI* NtQuerySystemTime)(PLARGE_INTEGER);

static DynamicLibrary _ntDll("ntdll.dll");
static NtQueryTimerResolution _ntQueryTimerResolution = (NtQueryTimerResolution)_ntDll.getFunction("NtQueryTimerResolution");
static NtSetTimerResolution _ntSetTimerResolution = (NtSetTimerResolution)_ntDll.getFunction("NtSetTimerResolution");
static NtCreateTimer _ntCreateTimer = (NtCreateTimer)_ntDll.getFunction("NtCreateTimer");
static NtSetTimer _ntSetTimer = (NtSetTimer)_ntDll.getFunction("NtSetTimer");
static NtClose _ntClose = (NtClose)_ntDll.getFunction("NtClose");
static NtQuerySystemTime _ntQuerySystemTime = (NtQuerySystemTime)_ntDll.getFunction("NtQuerySystemTime");

Timer::Timer(double delay, double interval, const Callback& callback)
{
	_delay = (LONGLONG)(delay * 10000000);
	_interval = (LONGLONG)(interval * 10000000);
	_callback = callback;
	_ntCreateTimer(&_timerHandle, TIMER_ALL_ACCESS, NULL, 0);
	_eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
	_threadHandle = CreateThread(NULL, 0, threadProc, this, 0, NULL);
}

Timer::~Timer()
{
	SetEvent(_eventHandle);
	WaitForSingleObject(_threadHandle, INFINITE);
	CloseHandle(_threadHandle);
	CloseHandle(_eventHandle);
	_ntClose(_timerHandle);
}

double Timer::setResolution(double resolution)
{
	ULONG minResolution = 0;
	ULONG maxResolution = 0;
	ULONG currentResolution = 0;
	_ntQueryTimerResolution(&minResolution, &maxResolution, &currentResolution);
	ULONG newResolution = (ULONG)(resolution * 10000000);
	newResolution = clamp(newResolution, maxResolution, minResolution);
	_ntSetTimerResolution(newResolution, TRUE, &currentResolution);
	_ntQueryTimerResolution(&minResolution, &maxResolution, &currentResolution);
	return currentResolution / 10000000.0;
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
		_ntSetTimer(timer->_timerHandle, &dueTime, NULL, NULL, FALSE, 0, NULL);
		int index = WaitForMultipleObjects(ARRAYSIZE(objects), objects, FALSE, INFINITE);
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
	_ntQuerySystemTime(&time);
	return time.QuadPart;
}
