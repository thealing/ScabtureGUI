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

	const FpsCounter& getFpsCounter() const;

	const Event* getChangeEvent() const;

	const Event* getFrameEvent() const;

private:

	void onFrame();

private:

	CaptureLock _lock;
	UniquePointer<VideoCapture> _capture;
	UniquePointer<EventDispatcher> _dispatcher;
	FpsCounter _fpsCounter;
	EventPool _changeEventPool;
	EventPool _frameEventPool;
};

