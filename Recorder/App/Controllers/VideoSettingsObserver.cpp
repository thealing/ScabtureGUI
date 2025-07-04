#include "VideoSettingsObserver.h"

VideoSettingsObserver::VideoSettingsObserver(VideoSettingsManager* videoSettingsManager, VideoCaptureFactory* videoCaptureFactory, VideoResizerFactory* videoResizerFactory, VideoEncoderFactory* videoEncoderFactory)
{
	_videoSettingsManager = videoSettingsManager;
	_videoCaptureFactory = videoCaptureFactory;
	_videoResizerFactory = videoResizerFactory;
	_videoEncoderFactory = videoEncoderFactory;
	_eventDispatcher.addEntry(videoSettingsManager->getChangeEvent(), BIND(VideoSettingsObserver, onSettingsChanged, this));
	_eventDispatcher.start();
	LogUtil::logDebug(L"VideoSettingsObserver: Started on thread %i.", _eventDispatcher.getThreadId());
}

VideoSettingsObserver::~VideoSettingsObserver()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"VideoSettingsObserver: Stopped.");
}

void VideoSettingsObserver::onSettingsChanged()
{
	LogUtil::logInfo(L"VideoSettingsObserver: Updating settings.");
	VideoSettings videoSettings = _videoSettingsManager->getSettings();
	updateVideoCaptureSettings(videoSettings);
	updateVideoResizerSettings(videoSettings);
	updateVideoEncoderSettings(videoSettings);
}

void VideoSettingsObserver::updateVideoCaptureSettings(const VideoSettings& videoSettings)
{
	CaptureSettings settings = {};
	settings.method = videoSettings.captureMethod;
	settings.frameRate = videoSettings.frameRate;
	settings.showCursor = videoSettings.showCursor;
	if (_videoCaptureFactory->setSettings(settings))
	{
		LogUtil::logInfo(L"VideoSettingsObserver: Video capture settings changed.");
	}
}

void VideoSettingsObserver::updateVideoResizerSettings(const VideoSettings& videoSettings)
{
	VideoResizerSettings settings = {};
	settings.resize = videoSettings.resize;
	settings.keepRatio = videoSettings.keepRatio;
	settings.width = videoSettings.width;
	settings.height = videoSettings.height;
	settings.mode = videoSettings.resizeMode;
	settings.quality = videoSettings.resizeQuality;
	if (_videoResizerFactory->setSettings(settings))
	{
		LogUtil::logInfo(L"VideoSettingsObserver: Video resizer settings changed.");
	}
}

void VideoSettingsObserver::updateVideoEncoderSettings(const VideoSettings& videoSettings)
{
	VideoEncoderSettings settings = {};
	settings.frameRate = videoSettings.frameRate;
	settings.bitRate = videoSettings.bitRate;
	settings.format = videoSettings.encodeFormat;
	if (_videoEncoderFactory->setSettings(settings))
	{
		LogUtil::logInfo(L"VideoSettingsObserver: Video encoder settings changed.");
	}
}
