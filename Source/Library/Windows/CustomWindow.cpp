#include "CustomWindow.h"

CustomWindow::CustomWindow(const wchar_t* className)
{
	WNDCLASS windowClass = {};
	windowClass.lpszClassName = className;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	_atom = RegisterClass(&windowClass);
}

CustomWindow::~CustomWindow()
{
	HMODULE module = GetModuleHandle(NULL);
	UnregisterClass(MAKEINTATOM(_atom), module);
}
