#include "VideoSettingsObserver.h"

VideoSettingsObserver::VideoSettingsObserver(VideoSettingsManager* videoSettingsManager, WindowCaptureFactory* windowCaptureFactory, ScreenCaptureFactory* screenCaptureFactory, VideoResizerFactory* videoResizerFactory, VideoEncoderFactory* videoEncoderFactory, MainWindow* mainWindow)
{
	_videoSettingsManager = videoSettingsManager;
	_windowCaptureFactory = windowCaptureFactory;
	_screenCaptureFactory = screenCaptureFactory;
	_videoResizerFactory = videoResizerFactory;
	_videoEncoderFactory = videoEncoderFactory;
	_mainWindow = mainWindow;
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
	updateWindowCaptureSettings(videoSettings);
	updateScreenCaptureSettings(videoSettings);
	updateVideoResizerSettings(videoSettings);
	updateVideoEncoderSettings(videoSettings);
	updateMainWindowSettings(videoSettings);
}

void VideoSettingsObserver::updateWindowCaptureSettings(const VideoSettings& videoSettings)
{
	WindowCaptureSettings settings = {};
	settings.method = videoSettings.windowCaptureMethod;
	settings.frameRate = videoSettings.frameRate;
	settings.showCursor = videoSettings.showCursor;
	if (_windowCaptureFactory->setSettings(settings))
	{
		LogUtil::logInfo(L"VideoSettingsObserver: Window capture settings changed.");
	}
}

void VideoSettingsObserver::updateScreenCaptureSettings(const VideoSettings& videoSettings)
{
	ScreenCaptureSettings settings = {};
	settings.method = videoSettings.screenCaptureMethod;
	settings.frameRate = videoSettings.frameRate;
	settings.showCursor = videoSettings.showCursor;
	if (_screenCaptureFactory->setSettings(settings))
	{
		LogUtil::logInfo(L"VideoSettingsObserver: Screen capture settings changed.");
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

void VideoSettingsObserver::updateMainWindowSettings(const VideoSettings& videoSettings)
{
	_mainWindow->excludeFromCapture(videoSettings.exclude);
}
