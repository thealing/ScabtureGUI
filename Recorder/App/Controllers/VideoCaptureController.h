#pragma once

class VideoCaptureController : NonCopyable
{
public:

	VideoCaptureController(VideoCaptureManager* videoCaptureManager, VideoCaptureFactory* videoCaptureFactory, VideoResizerFactory* videoResizerFactory, VideoSourceManager* videoSourceManager, VideoSettingsManager* videoSettingsManager, KeyboardListener* keyboardListener);

	~VideoCaptureController();

private:

	void onCaptureFailed();

	void onCaptureChanged();

	void onResizerChanged();

	void onRefreshHotkeyPressed();

	void updateCapture();

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
	WeakPointer<VideoCaptureFactory> _videoCaptureFactory;
	WeakPointer<VideoResizerFactory> _videoResizerFactory;
	WeakPointer<VideoSourceManager> _videoSourceManager;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
	WeakPointer<KeyboardListener> _keyboardListener;
};

