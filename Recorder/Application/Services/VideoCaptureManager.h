#pragma once

class VideoCaptureManager : NonCopyable
{
public:

	VideoCaptureManager();

	~VideoCaptureManager();

	void reset();

	void setCapture(VideoCapture* capture);

	VideoCapture* lockCapture();

	void unlockCapture();

	const Event* getChangeEvent();

	const Event* getFrameEvent();

	const Event* getErrorEvent();

	const FpsCounter& getFpsCounter() const;

private:

	void onFrame();

	void onError();

private:

	CaptureLock _lock;
	UniquePointer<VideoCapture> _capture;
	UniquePointer<EventDispatcher> _dispatcher;
	EventPool _changeEventPool;
	EventPool _frameEventPool;
	EventPool _errorEventPool;
	FpsCounter _fpsCounter;
};

