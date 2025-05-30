#pragma once

class FrameSink : NonCopyable
{
public:

	FrameSink(FrameSource* source);

	virtual ~FrameSink();

protected:

	void start();

	void stop();

	virtual void onFrame() = 0;

	virtual void onError() = 0;

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<FrameSource> _source;
	WeakPointer<const Event> _frameEvent;
	WeakPointer<const Event> _errorEvent;
};

