#pragma once

class FrameSource : NonCopyable
{
public:

	const Event* getFrameEvent() const;

protected:

	void signalFrame();

private:

	EventPool _frameEventPool;
};

