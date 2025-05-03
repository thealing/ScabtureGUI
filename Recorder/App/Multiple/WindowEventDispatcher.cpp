#include "WindowEventDispatcher.h"

WindowEventDispatcher::WindowEventDispatcher(Window* window)
{
	_window = window;
}

void WindowEventDispatcher::onEvent(int index)
{
	_window->postTask(_callbacks[index]);
}
