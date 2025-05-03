#pragma once

class ExclusiveLock : NonCopyable
{
public:

	ExclusiveLock();

	void acquire();

	void release();

private:

	SRWLOCK _lock;
};

class ExclusiveLockHolder : NonCopyable
{
public:

	ExclusiveLockHolder(ExclusiveLock* lock);

	~ExclusiveLockHolder();

private:

	ExclusiveLock* _lock;
};
