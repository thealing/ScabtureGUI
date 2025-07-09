#pragma once

class CaptureLock : NonCopyable
{
public:

	CaptureLock();

	~CaptureLock();

	void beginReading();

	void endReading();

	void beginWriting();

	void endWriting();

private:

	CRITICAL_SECTION _criticalSection;
	CONDITION_VARIABLE _conditionVariable;
	int _counter;
};
