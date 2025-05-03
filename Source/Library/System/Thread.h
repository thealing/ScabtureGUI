#pragma once

class Thread : NonCopyable
{
public:

	Thread(const Callback& callback);

	~Thread();

	int getId() const;

private:

	Callback* _callback;
	HANDLE _handle;

private:

	static DWORD WINAPI threadProc(LPVOID parameter);
};

