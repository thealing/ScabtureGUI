#include "AudioCaptureManager.h"

AudioCaptureManager::AudioCaptureManager()
{
}

void AudioCaptureManager::setCapture(AudioCapture* capture)
{
	_lock.beginWriting();
	_capture = capture;
	_lock.endWriting();
}

AudioCapture* AudioCaptureManager::lockCapture()
{
	_lock.beginReading();
	return _capture;
}

void AudioCaptureManager::unlockCapture()
{
	_lock.endReading();
}
