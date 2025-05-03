#pragma once

// This is a custom read-write lock implementation which solves an issue with the SRWLock. 
// SRWLock is designed to avoid writer-starvation, so when an exclusive acquisition is requested,
// it doesn't allow any more shared acquisitions, until all of them are released, and the write completes. 
// This version blocks the write request until all reader locks are released,
// while still allowing new readers to acquire the lock.
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
