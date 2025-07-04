#include "WindowCapture.h"

WindowCapture::WindowCapture(HWND window, int frameRate, bool showCursor)
{
	_window = window;
	_capture = new BitBltGetBitmapBitsCapture(window);
	if (showCursor)
	{
		RECT clientRect = WindowUtil::getRelativeClientRect(window);
		POINT clientOffset = { clientRect.left, clientRect.top };
		Overlay* mouseOverlay = new MouseOverlay(window, clientOffset);
		_capture->addOverlay(mouseOverlay);
	}
	_timer = new Timer(0, 1.0 / frameRate, BIND(WindowCapture, onTimer, this));
}

const Buffer* WindowCapture::getBuffer() const
{
	return _capture->getBuffer();
}

void WindowCapture::onTimer()
{
	if (_window == NULL)
	{
		return;
	}
	if (!IsWindow(_window))
	{
		_window = NULL;
		signalError();
		return;
	}
	if (IsIconic(_window))
	{
		return;
	}
	if (_capture->getFrame())
	{
		signalFrame();
	}
}
