#pragma once

class WindowClass : NonCopyable
{
public:

	WindowClass(const wchar_t* name);

	~WindowClass();

private:

	ATOM _atom;
};

