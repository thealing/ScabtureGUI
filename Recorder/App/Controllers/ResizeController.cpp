#include "ResizeController.h"

ResizeController::ResizeController(ResizePanel* resizePanel, WindowSourceManager* windowSourceManager, VideoCaptureManager* videoCaptureManager, VideoSettingsManager* videoSettingsManager)
{
	_resizePanel = resizePanel;
	_windowSourceManager = windowSourceManager;
	_videoCaptureManager = videoCaptureManager;
	_videoSettingsManager = videoSettingsManager;
	_eventDispatcher.addEntry(resizePanel->getWidthChangeEvent(), BIND(ResizeController, onWidthChanged, this));
	_eventDispatcher.addEntry(resizePanel->getHeightChangeEvent(), BIND(ResizeController, onHeightChanged, this));
	_eventDispatcher.addEntry(resizePanel->getResizeChangeEvent(), BIND(ResizeController, onResizeChanged, this));
	_eventDispatcher.addEntry(resizePanel->getKeepRatioChangeEvent(), BIND(ResizeController, onKeepRatioChanged, this));
	_eventDispatcher.addEntry(videoCaptureManager->getChangeEvent(), BIND(ResizeController, onVideoCaptureChanged, this));
	_eventDispatcher.addEntry(videoSettingsManager->getChangeEvent(), BIND(ResizeController, onVideoSettingsChanged, this));
	_eventDispatcher.start(resizePanel);
	LogUtil::logDebug(L"ResizeController: Started on thread %i.", _eventDispatcher.getThreadId());
}

ResizeController::~ResizeController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"ResizeController: Stopped.");
}

void ResizeController::onWidthChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	int width = _resizePanel->getWidth();
	if (settings.width != width)
	{
		LogUtil::logInfo(L"ResizeController: Width modified to %i by the user.", width);
		settings.width = width;
		if (settings.doResize && settings.keepRatio)
		{
			Vector size = _windowSourceManager->getWindowSize();
			int height = width * size.y / max(1, size.x);
			LogUtil::logInfo(L"ResizeController: Adjusted height to %i to keep the aspect ratio.", height);
			settings.height = height;
		}
		_videoSettingsManager->setSettings(settings);
	}
}

void ResizeController::onHeightChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	int height = _resizePanel->getHeight();
	if (settings.height != height)
	{
		LogUtil::logInfo(L"ResizeController: Height modified to %i by the user.", height);
		settings.height = height;
		if (settings.doResize && settings.keepRatio)
		{
			Vector size = _windowSourceManager->getWindowSize();
			int width = height * size.x / max(1, size.y);
			LogUtil::logInfo(L"ResizeController: Adjusted width to %i to keep the aspect ratio.", height);
			settings.width = width;
		}
		_videoSettingsManager->setSettings(settings);
	}
}

void ResizeController::onResizeChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	bool resize = _resizePanel->getResize();
	if (settings.doResize != resize)
	{
		LogUtil::logInfo(L"ResizeController: Resize flag modified to %i by the user.", resize);
		settings.doResize = resize;
		_videoSettingsManager->setSettings(settings);
	}
}

void ResizeController::onKeepRatioChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	bool keepRatio = _resizePanel->getKeepRatio();
	if (settings.keepRatio != keepRatio)
	{
		LogUtil::logInfo(L"ResizeController: Keep ratio flag modified to %i by the user.", keepRatio);
		settings.keepRatio = keepRatio;
		if (settings.doResize && settings.keepRatio)
		{
			Vector size = _windowSourceManager->getWindowSize();
			settings.width = min(settings.width, settings.height * size.x / max(1, size.y));
			settings.height = min(settings.height, settings.width * size.y / max(1, size.x));
			LogUtil::logInfo(L"ResizeController: Adjusted capture size to %ix%i.", settings.width, settings.height);
		}
		_videoSettingsManager->setSettings(settings);
	}
}

void ResizeController::onVideoCaptureChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	VideoCapture* capture = _videoCaptureManager->lockCapture();
	if (capture != NULL)
	{
		const Buffer* buffer = capture->getBuffer();
		settings.width = buffer->getWidth();
		settings.height = buffer->getHeight();
	}
	_videoCaptureManager->unlockCapture();
	LogUtil::logInfo(L"ResizeController: Capture size changed to %ix%i.", settings.width, settings.height);
	_videoSettingsManager->setSettings(settings);
}

void ResizeController::onVideoSettingsChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	int visibleWidth = _resizePanel->getWidth();
	if (settings.width != visibleWidth)
	{
		LogUtil::logInfo(L"ResizeController: Width setting changed to %i.", settings.width);
		_resizePanel->setWidth(settings.width);
	}
	int visibleHeight = _resizePanel->getHeight();
	if (settings.height != visibleHeight)
	{
		LogUtil::logInfo(L"ResizeController: Height setting changed to %i.", settings.height);
		_resizePanel->setHeight(settings.height);
	}
	bool resizeFlag = _resizePanel->getResize();
	if (settings.doResize != resizeFlag)
	{
		LogUtil::logInfo(L"ResizeController: Resize setting changed to %i.", settings.doResize);
		_resizePanel->setResize(settings.doResize);
	}
	bool keepRatio = _resizePanel->getKeepRatio();
	if (settings.keepRatio != keepRatio)
	{
		LogUtil::logInfo(L"ResizeController: Keep ratio setting changed to %i.", settings.keepRatio);
		_resizePanel->setKeepRatio(settings.keepRatio);
	}
	_resizePanel->setEnabled(settings.doResize);
}
