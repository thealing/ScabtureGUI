#include "VideoSettingsObserver.h"

VideoSettingsObserver::VideoSettingsObserver(VideoSettingsManager* videoSettingsManager, WindowSourceManager* windowSourceManager, VideoResizerFactory* videoResizerFactory, VideoEncoderFactory* videoEncoderFactory)
{
	_videoSettingsManager = videoSettingsManager;
	_windowSourceManager = windowSourceManager;
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
	updateWindowSourceSettings(videoSettings);
	updateVideoResizerSettings(videoSettings);
	updateVideoEncoderSettings(videoSettings);
}

void VideoSettingsObserver::updateWindowSourceSettings(const VideoSettings& videoSettings)
{
	WindowSourceSettings settings = {};
	settings.area = videoSettings.windowArea;
	settings.captureSettings.method = videoSettings.captureMethod;
	settings.captureSettings.frameRate = videoSettings.frameRate;
	settings.captureSettings.showCursor = videoSettings.showCursor;
	if (_windowSourceManager->setSettings(settings))
	{
		LogUtil::logInfo(L"VideoSettingsObserver: Window source settings changed.");
	}
}

void VideoSettingsObserver::updateVideoResizerSettings(const VideoSettings& videoSettings)
{
	VideoResizerSettings settings = {};
	settings.doResize = videoSettings.doResize;
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
