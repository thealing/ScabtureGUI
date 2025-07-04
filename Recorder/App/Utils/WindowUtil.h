#pragma once

class WindowUtil
{
public:

	static POINT getWindowPosition(HWND window);

	static RECT getAbsoluteClientRect(HWND window);

	static RECT getRelativeClientRect(HWND window);
};
