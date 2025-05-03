#pragma once

class Timer : NonCopyable
{
public:

	Timer(double delay, double interval, const Callback& callback);

	~Timer();

private:

	LONGLONG _delay;
	LONGLONG _interval;
	Callback _callback;
	HANDLE _timerHandle;
	HANDLE _eventHandle;
	HANDLE _threadHandle;

public:

	static double setResolution(double resolution);

private:

	static DWORD WINAPI threadProc(PVOID parameter);

	static LONGLONG getSystemTime();
};
