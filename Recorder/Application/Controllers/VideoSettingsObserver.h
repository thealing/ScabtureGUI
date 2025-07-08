#pragma once

class VideoSettingsObserver : NonCopyable
{
public:

	VideoSettingsObserver(VideoSettingsManager* videoSettingsManager, WindowCaptureFactory* windowCaptureFactory, ScreenCaptureFactory* screenCaptureFactory, VideoResizerFactory* videoResizerFactory, VideoEncoderFactory* videoEncoderFactory);

	~VideoSettingsObserver();

private:

	void onSettingsChanged();

	void updateWindowCaptureSettings(const VideoSettings& videoSettings);

	void updateScreenCaptureSettings(const VideoSettings& videoSettings);

	void updateVideoResizerSettings(const VideoSettings& videoSettings);

	void updateVideoEncoderSettings(const VideoSettings& videoSettings);

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
	WeakPointer<WindowCaptureFactory> _windowCaptureFactory;
	WeakPointer<ScreenCaptureFactory> _screenCaptureFactory;
	WeakPointer<VideoResizerFactory> _videoResizerFactory;
	WeakPointer<VideoEncoderFactory> _videoEncoderFactory;
};

