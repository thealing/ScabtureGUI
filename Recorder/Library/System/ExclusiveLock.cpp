#include "ExclusiveLock.h"

ExclusiveLock::ExclusiveLock()
{
	InitializeSRWLock(&_lock);
}

void ExclusiveLock::acquire()
{
	AcquireSRWLockExclusive(&_lock);
}

void ExclusiveLock::release()
{
	ReleaseSRWLockExclusive(&_lock);
}

ExclusiveLockHolder::ExclusiveLockHolder(ExclusiveLock* lock)
{
	_lock = lock;
	_lock->acquire();
}

ExclusiveLockHolder::~ExclusiveLockHolder()
{
	_lock->release();
}
