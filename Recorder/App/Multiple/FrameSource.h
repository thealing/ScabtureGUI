#pragma once

class FrameSource : NonCopyable
{
public:

	FrameSource();

	const Event* getFrameEvent();

	void releaseFrameEvent(const Event* event);

protected:

	void signalFrame();

private:

	static const int Capacity = 4;

	Event _events[Capacity];
	bool _used[Capacity];
};

