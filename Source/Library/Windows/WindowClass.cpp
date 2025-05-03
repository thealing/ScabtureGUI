#include "WindowClass.h"

WindowClass::WindowClass(const wchar_t* name)
{
	WNDCLASS windowClass = {};
	windowClass.lpszClassName = name;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_atom = RegisterClass(&windowClass);
}

WindowClass::~WindowClass()
{
	HMODULE module = GetModuleHandle(NULL);
	UnregisterClass(MAKEINTATOM(_atom), module);
}
