#pragma once

class VideoCaptureController : NonCopyable
{
public:

	VideoCaptureController(VideoCaptureManager* videoCaptureManager, VideoResizerFactory* videoResizerFactory, WindowSourceManager* windowCaptureManager, VideoSettingsManager* videoSettingsManager, KeyboardListener* keyboardListener);

	~VideoCaptureController();

private:

	void onCaptureFailed();

	void onSourceChanged();

	void onResizerChanged();

	void onRefreshHotkeyPressed();

	void updateCapture();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
	WeakPointer<VideoResizerFactory> _videoResizerFactory;
	WeakPointer<WindowSourceManager> _windowSourceManager;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
	WeakPointer<KeyboardListener> _keyboardListener;
};

