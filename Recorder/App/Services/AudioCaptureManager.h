#pragma once

class AudioCaptureManager : NonCopyable
{
public:

	AudioCaptureManager();

	~AudioCaptureManager();

	void setCapture(AudioCapture* capture);

	AudioCapture* lockCapture();

	void unlockCapture();

	const Event* getErrorEvent() const;

private:

	void onError();

private:

	ReadWriteLock _lock;
	UniquePointer<AudioCapture> _capture;
	UniquePointer<EventDispatcher> _dispatcher;
	EventPool _errorEventPool;
};

