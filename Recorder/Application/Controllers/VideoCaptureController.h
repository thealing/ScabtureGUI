#pragma once

class VideoCaptureController : NonCopyable
{
public:

	VideoCaptureController(VideoCaptureManager* videoCaptureManager, WindowCaptureFactory* windowCaptureFactory, ScreenCaptureFactory* screenCaptureFactory, VideoResizerFactory* videoResizerFactory, VideoSourceManager* videoSourceManager, VideoSettingsManager* videoSettingsManager, KeyboardListener* keyboardListener);

	~VideoCaptureController();

private:

	void onCaptureFailed();

	void onWindowCaptureChanged();

	void onScreenCaptureChanged();

	void onResizerChanged();

	void onSourceChanged();

	void onSourceSizeChanged();

	void onSourceDestroyed();

	void onRefreshHotkeyPressed();

	void updateCapture();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
	WeakPointer<WindowCaptureFactory> _windowCaptureFactory;
	WeakPointer<ScreenCaptureFactory> _screenCaptureFactory;
	WeakPointer<VideoResizerFactory> _videoResizerFactory;
	WeakPointer<VideoSourceManager> _videoSourceManager;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
	WeakPointer<KeyboardListener> _keyboardListener;
};

