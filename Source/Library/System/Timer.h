#pragma once

class Timer : NonCopyable
{
public:

	static double setResolution(double resolution);

	Timer(double delay, double interval, const Callback& callback);

	~Timer();

private:

	typedef NTSTATUS NTAPI NtClose(HANDLE);
	typedef NTSTATUS NTAPI NtCreateTimer(PHANDLE, ACCESS_MASK, void*, DWORD);
	typedef NTSTATUS NTAPI NtSetTimer(HANDLE, PLARGE_INTEGER, PVOID, PVOID, BOOLEAN, LONG, PBOOLEAN);
	typedef NTSTATUS NTAPI NtQuerySystemTime(PLARGE_INTEGER);
	typedef NTSTATUS NTAPI NtQueryTimerResolution(PULONG, PULONG, PULONG);
	typedef NTSTATUS NTAPI NtSetTimerResolution(ULONG, BOOLEAN, PULONG);

	LONGLONG _delay;
	LONGLONG _interval;
	Callback _callback;
	HANDLE _timerHandle;
	HANDLE _eventHandle;
	HANDLE _threadHandle;

private:

	static DWORD WINAPI threadProc(PVOID parameter);

	static LONGLONG getSystemTime();

	static BOOL ntClose(HANDLE handle);

	static BOOL ntCreateTimer(PHANDLE timerHandle, ACCESS_MASK desiredAccess, void* objectAttributes, DWORD timerType);

	static BOOL ntSetTimer(HANDLE timerHandle, PLARGE_INTEGER dueTime, PVOID timerApcRoutine, PVOID timerContext, BOOLEAN resume, LONG period, PBOOLEAN previousState);

	static BOOL ntQuerySystemTime(PLARGE_INTEGER currentTime);

	static BOOL ntQueryTimerResolution(PULONG minimumResolution, PULONG maximumResolution, PULONG currentResolution);

	static BOOL ntSetTimerResolution(ULONG desiredResolution, BOOLEAN setResolution, PULONG currentResolution);
};
