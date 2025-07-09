#include "ResizeController.h"

ResizeController::ResizeController(ResizePanel* resizePanel, VideoCaptureManager* videoCaptureManager, VideoSettingsManager* videoSettingsManager)
{
	_resizePanel = resizePanel;
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
		LogUtil::logInfo(L"ResizeController: Width modified to %i.", width);
		settings.width = width;
		if (settings.resize && settings.keepRatio)
		{
			settings.height = 0;
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
		LogUtil::logInfo(L"ResizeController: Height modified to %i.", height);
		settings.height = height;
		if (settings.resize && settings.keepRatio)
		{
			settings.width = 0;
		}
		_videoSettingsManager->setSettings(settings);
	}
}

void ResizeController::onResizeChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	bool resize = _resizePanel->getResize();
	if (settings.resize != resize)
	{
		LogUtil::logInfo(L"ResizeController: Resize flag modified to %i.", resize);
		settings.resize = resize;
		if (settings.resize)
		{
			VideoCapture* capture = _videoCaptureManager->lockCapture();
			if (capture != NULL)
			{
				const Buffer* buffer = capture->getBuffer();
				settings.width = buffer->getWidth();
				settings.height = buffer->getHeight();
			}
			_videoCaptureManager->unlockCapture();
		}
		_videoSettingsManager->setSettings(settings);
	}
}

void ResizeController::onKeepRatioChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	bool keepRatio = _resizePanel->getKeepRatio();
	if (settings.keepRatio != keepRatio)
	{
		LogUtil::logInfo(L"ResizeController: Keep ratio flag modified to %i.", keepRatio);
		settings.keepRatio = keepRatio;
		if (!settings.keepRatio)
		{
			VideoCapture* capture = _videoCaptureManager->lockCapture();
			if (capture != NULL)
			{
				const Buffer* buffer = capture->getBuffer();
				settings.width = buffer->getWidth();
				settings.height = buffer->getHeight();
			}
			_videoCaptureManager->unlockCapture();
		}
		_videoSettingsManager->setSettings(settings);
	}
}

void ResizeController::onVideoCaptureChanged()
{
	VideoCapture* capture = _videoCaptureManager->lockCapture();
	if (capture != NULL)
	{
		const Buffer* buffer = capture->getBuffer();
		int width = buffer->getWidth();
		if (_resizePanel->getWidth() != width)
		{
			LogUtil::logInfo(L"ResizeController: Width changed to %i.", width);
			_resizePanel->setWidth(width);
		}
		int height = buffer->getHeight();
		if (_resizePanel->getHeight() != height)
		{
			LogUtil::logInfo(L"ResizeController: Height changed to %i.", height);
			_resizePanel->setHeight(height);
		}
	}
	_videoCaptureManager->unlockCapture();
}

void ResizeController::onVideoSettingsChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	bool resizeFlag = _resizePanel->getResize();
	if (settings.resize != resizeFlag)
	{
		LogUtil::logInfo(L"ResizeController: Resize setting changed to %i.", settings.resize);
		_resizePanel->setResize(settings.resize);
	}
	bool keepRatio = _resizePanel->getKeepRatio();
	if (settings.keepRatio != keepRatio)
	{
		LogUtil::logInfo(L"ResizeController: Keep ratio setting changed to %i.", settings.keepRatio);
		_resizePanel->setKeepRatio(settings.keepRatio);
	}
	_resizePanel->setEnabled(settings.resize);
}
