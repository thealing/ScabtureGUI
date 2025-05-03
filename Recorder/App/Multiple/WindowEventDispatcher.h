#pragma once

class WindowEventDispatcher : public EventDispatcher
{
public:

	WindowEventDispatcher(Window* window);

private:

	virtual void onEvent(int index) override;

private:

	Window* _window;
};

