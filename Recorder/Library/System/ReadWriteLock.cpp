#include "ReadWriteLock.h"

ReadWriteLock::ReadWriteLock()
{
	InitializeSRWLock(&_lock);
}

void ReadWriteLock::beginReading()
{
	AcquireSRWLockShared(&_lock);
}

void ReadWriteLock::endReading()
{
	ReleaseSRWLockShared(&_lock);
}

void ReadWriteLock::beginWriting()
{
	AcquireSRWLockExclusive(&_lock);
}

void ReadWriteLock::endWriting()
{
	ReleaseSRWLockExclusive(&_lock);
}

bool ReadWriteLock::tryReading()
{
    return TryAcquireSRWLockShared(&_lock);
}

bool ReadWriteLock::tryWriting()
{
	return TryAcquireSRWLockExclusive(&_lock);
}

ReadLockHolder::ReadLockHolder(ReadWriteLock* lock)
{
	_lock = lock;
	_lock->beginReading();
}

ReadLockHolder::~ReadLockHolder()
{
	_lock->endReading();
}

WriteLockHolder::WriteLockHolder(ReadWriteLock* lock)
{
	_lock = lock;
	_lock->beginWriting();
}

WriteLockHolder::~WriteLockHolder()
{
	_lock->endWriting();
}
