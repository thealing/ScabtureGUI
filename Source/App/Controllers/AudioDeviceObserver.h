#pragma once

class AudioDeviceObserver : NonCopyable
{
public:

	AudioDeviceObserver(AudioDeviceProvider* audioDeviceProvider, AudioVolumeListener* audioVolumeListener);

	~AudioDeviceObserver();

private:

	void onInputDeviceChanged();

	void onOutputDeviceChanged();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<AudioDeviceProvider> _audioDeviceProvider;
	WeakPointer<AudioVolumeListener> _audioVolumeListener;
};


