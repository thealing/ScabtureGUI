#include "WindowEventDispatcher.h"

WindowEventDispatcher::WindowEventDispatcher()
{
	_window = NULL;
}

void WindowEventDispatcher::start(Window* window)
{
	_window = window;
	BaseEventDispatcher::start();
}

void WindowEventDispatcher::stop()
{
	BaseEventDispatcher::stop();
	_window = NULL;
}

void WindowEventDispatcher::onEvent(int index)
{
	_window->postTask(_callbacks[index]);
}
