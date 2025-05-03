#include "AudioCapture.h"

AudioCapture::~AudioCapture()
{
}

void AudioCapture::setCallback(const Callback& callback)
{
	_callback = callback;
}

void AudioCapture::invokeCallback()
{
	_callback.invoke();
}
