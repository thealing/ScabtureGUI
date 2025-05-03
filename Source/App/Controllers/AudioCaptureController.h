#pragma once

class AudioCaptureController : NonCopyable
{
public:

	AudioCaptureController(AudioCaptureManager* audioCaptureManager, AudioResamplerFactory* audioResamplerFactory, AudioDeviceProvider* audioDeviceProvider, AudioSourceManager* audioSourceManager);

	~AudioCaptureController();

private:

	void onInputDeviceChanged(); 

	void onOutputDeviceChanged();

	void onResamplerChanged();

	void onSourceChanged();

	void updateCapture();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<AudioCaptureManager> _audioCaptureManager;
	WeakPointer<AudioResamplerFactory> _audioResamplerFactory;
	WeakPointer<AudioDeviceProvider> _audioDeviceProvider;
	WeakPointer<AudioSourceManager> _audioSourceManager;
};

