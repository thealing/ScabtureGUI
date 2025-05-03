#pragma once

class VideoSettingsObserver : NonCopyable
{
public:

	VideoSettingsObserver(VideoSettingsManager* videoSettingsManager, WindowSourceManager* windowSourceManager, VideoResizerFactory* videoResizerFactory, VideoEncoderFactory* videoEncoderFactory);

	~VideoSettingsObserver();

private:

	void onSettingsChanged();

	void updateWindowSourceSettings(const VideoSettings& videoSettings);

	void updateVideoResizerSettings(const VideoSettings& videoSettings);

	void updateVideoEncoderSettings(const VideoSettings& videoSettings);

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
	WeakPointer<WindowSourceManager> _windowSourceManager;
	WeakPointer<VideoResizerFactory> _videoResizerFactory;
	WeakPointer<VideoEncoderFactory> _videoEncoderFactory;
};

