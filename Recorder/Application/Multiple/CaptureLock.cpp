#include "CaptureLock.h"

CaptureLock::CaptureLock()
{
	InitializeCriticalSection(&_criticalSection);
	InitializeConditionVariable(&_conditionVariable);
	_counter = 0;
}

CaptureLock::~CaptureLock()
{
	DeleteCriticalSection(&_criticalSection);
}

void CaptureLock::beginReading()
{
	EnterCriticalSection(&_criticalSection);
	while (_counter < 0)
	{
		SleepConditionVariableCS(&_conditionVariable, &_criticalSection, INFINITE);
	}
	_counter++;
	LeaveCriticalSection(&_criticalSection);
}

void CaptureLock::endReading()
{
	EnterCriticalSection(&_criticalSection);
	_counter--;
	if (_counter == 0)
	{
		WakeAllConditionVariable(&_conditionVariable);
	}
	LeaveCriticalSection(&_criticalSection);
}

void CaptureLock::beginWriting()
{
	EnterCriticalSection(&_criticalSection);
	while (_counter != 0)
	{
		SleepConditionVariableCS(&_conditionVariable, &_criticalSection, INFINITE);
	}
	_counter--;
	LeaveCriticalSection(&_criticalSection);
}

void CaptureLock::endWriting()
{
	EnterCriticalSection(&_criticalSection);
	_counter++;
	if (_counter == 0)
	{
		WakeAllConditionVariable(&_conditionVariable);
	}
	LeaveCriticalSection(&_criticalSection);
}
