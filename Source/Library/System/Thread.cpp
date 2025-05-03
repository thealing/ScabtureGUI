#include "Thread.h"

Thread::Thread(const Callback& callback)
{
	_callback = new Callback(callback);
	_handle = CreateThread(NULL, 0, threadProc, _callback, 0, NULL);
}

Thread::~Thread()
{
	if (_handle != NULL)
	{
		WaitForSingleObject(_handle, INFINITE);
		CloseHandle(_handle);
	}
	if (_callback != NULL)
	{
		delete _callback;
	}
}

int Thread::getId() const
{
    return GetThreadId(_handle);
}

DWORD WINAPI Thread::threadProc(LPVOID parameter)
{
	Callback* callback = (Callback*)parameter;
	callback->invoke();
	return 0;
}
