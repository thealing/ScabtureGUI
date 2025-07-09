#pragma once

class AudioCaptureController : NonCopyable
{
public:

	AudioCaptureController(AudioCaptureManager* audioCaptureManager, AudioResamplerFactory* audioResamplerFactory, AudioDeviceProvider* audioDeviceProvider, AudioSourceManager* audioSourceManager, MainWindow* mainWindow);

	~AudioCaptureController();

private:

	void onInputDeviceChanged(); 

	void onOutputDeviceChanged();

	void onResamplerChanged();

	void onSourceChanged();

	void onCaptureError();

	void updateCapture();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<AudioCaptureManager> _audioCaptureManager;
	WeakPointer<AudioResamplerFactory> _audioResamplerFactory;
	WeakPointer<AudioDeviceProvider> _audioDeviceProvider;
	WeakPointer<AudioSourceManager> _audioSourceManager;
	WeakPointer<MainWindow> _mainWindow;
};

