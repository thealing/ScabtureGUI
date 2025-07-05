#pragma once

class WindowCapture : public ScreenCapture
{
public:

	WindowCapture(HWND window, int frameRate, bool showCursor);
};

