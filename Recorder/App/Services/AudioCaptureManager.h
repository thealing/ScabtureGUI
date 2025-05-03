#pragma once

class AudioCaptureManager : NonCopyable
{
public:

	AudioCaptureManager();

	void setCapture(AudioCapture* capture);

	AudioCapture* lockCapture();

	void unlockCapture();

private:

	ReadWriteLock _lock;
	UniquePointer<AudioCapture> _capture;
};

