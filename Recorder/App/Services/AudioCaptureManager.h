#pragma once

class AudioCaptureManager : NonCopyable
{
public:

	AudioCaptureManager();

	~AudioCaptureManager();

	const Event* getErrorEvent();

	void setCapture(AudioCapture* capture);

	AudioCapture* lockCapture();

	void unlockCapture();

private:

	void onError();

private:

	ReadWriteLock _lock;
	UniquePointer<AudioCapture> _capture;
	UniquePointer<EventDispatcher> _dispatcher;
	EventPool _errorEventPool;
};

