#pragma once

class AudioDeviceObserver : NonCopyable
{
public:

	AudioDeviceObserver(AudioDeviceProvider* audioDeviceProvider, AudioVolumeListener* audioVolumeListener, AudioResamplerFactory* audioResamplerFactory);

	~AudioDeviceObserver();

private:

	void onInputDeviceChanged();

	void onOutputDeviceChanged();

	void onInputMeterError();

	void onOutputMeterError();

	void onResamplerChanged();

	void updateInputDevice();

	void updateOutputDevice();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<AudioDeviceProvider> _audioDeviceProvider;
	WeakPointer<AudioVolumeListener> _audioVolumeListener;
	WeakPointer<AudioResamplerFactory> _audioResamplerFactory;
};


