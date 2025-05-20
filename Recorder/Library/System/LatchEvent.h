#pragma once

class LatchEvent : NonCopyable
{
public:

	LatchEvent();

	~LatchEvent();

	bool set();

	bool reset();

	void wait() const;

private:

	HANDLE _handle;
};

