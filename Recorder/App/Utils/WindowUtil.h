#pragma once

class WindowUtil
{
public:

	static HWND getDesktopWindow();

	static POINT getWindowPosition(HWND window);

	static HWND findWindowUnderPoint(POINT point, HWND windowToSkip);

	static RECT getAbsoluteRect(HWND window, WindowArea area);

	static RECT getRelativeRect(HWND window, WindowArea area);
};
