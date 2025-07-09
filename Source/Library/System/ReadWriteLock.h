#pragma once

class ReadWriteLock : NonCopyable
{
public:

	ReadWriteLock();

	void beginReading();

	void endReading();

	void beginWriting();

	void endWriting();

	bool tryReading();

	bool tryWriting();

private:

	SRWLOCK _lock;
};

class ReadLockHolder : NonCopyable
{
public:

	ReadLockHolder(ReadWriteLock* lock);

	~ReadLockHolder();

private:

	ReadWriteLock* _lock;
};

class WriteLockHolder : NonCopyable
{
public:

	WriteLockHolder(ReadWriteLock* lock);

	~WriteLockHolder();

private:

	ReadWriteLock* _lock;
};
