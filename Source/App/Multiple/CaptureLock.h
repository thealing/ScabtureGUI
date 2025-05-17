#pragma once

// This is a custom read-write lock implementation, for correct locking of the video capture.
// When a writer lock is requested, it waits until all reader locks are released, while still allowing new reader locks to be acquired.
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
