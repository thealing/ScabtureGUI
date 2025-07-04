#pragma once

class VideoSettingsObserver : NonCopyable
{
public:

	VideoSettingsObserver(VideoSettingsManager* videoSettingsManager, VideoCaptureFactory* videoCaptureFactory, VideoResizerFactory* videoResizerFactory, VideoEncoderFactory* videoEncoderFactory);

	~VideoSettingsObserver();

private:

	void onSettingsChanged();

	void updateVideoCaptureSettings(const VideoSettings& videoSettings);

	void updateVideoResizerSettings(const VideoSettings& videoSettings);

	void updateVideoEncoderSettings(const VideoSettings& videoSettings);

private:

	EventDispatcher _eventDispatcher;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
	WeakPointer<VideoCaptureFactory> _videoCaptureFactory;
	WeakPointer<VideoResizerFactory> _videoResizerFactory;
	WeakPointer<VideoEncoderFactory> _videoEncoderFactory;
};

