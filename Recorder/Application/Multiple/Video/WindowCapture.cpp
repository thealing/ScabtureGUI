#include "WindowCapture.h"

WindowCapture::WindowCapture(HWND window)
{
	_window = window;
}

void WindowCapture::start(int frameRate)
{
	_timer = new Timer(0, 1.0 / frameRate, BIND(WindowCapture, update, this));
}

void WindowCapture::stop()
{
	_timer = NULL;
}

HWND WindowCapture::getWindow() const
{
	return _window;
}

void WindowCapture::update()
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
	captureFrame();
}
