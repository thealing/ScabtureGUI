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

	EventPool _frameEventPool;
};

