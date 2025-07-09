#pragma once

class WindowEventDispatcher : public EventDispatcher
{
public:

	WindowEventDispatcher();

	void start(Window* window);

	void stop();

private:

	virtual void onEvent(int index) override;

private:

	Window* _window;
};

