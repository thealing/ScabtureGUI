#pragma once

class FrameSink : Virtual
{
public:

	FrameSink(FrameSource* source);

	~FrameSink();

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

