#include "Event.h"

int Event::waitOne(const Event** events, int count)
{
	return wait(events, count, false);
}

int Event::waitAll(const Event** events, int count)
{
	return wait(events, count, true);
}

int Event::wait(const Event** events, int count, bool all)
{
	HANDLE* handles = new HANDLE[count];
	for (int i = 0; i < count; i++)
	{
		handles[i] = events[i]->_handle;
	}
	DWORD result = WaitForMultipleObjects(count, handles, all, INFINITE);
	delete[] handles;
	return (int)result;
}

Event::Event()
{
	_handle = CreateEvent(NULL, FALSE, FALSE, NULL);
}

Event::~Event()
{
	CloseHandle(_handle);
}

void Event::set()
{
	SetEvent(_handle);
}

void Event::reset()
{
	ResetEvent(_handle);
}
