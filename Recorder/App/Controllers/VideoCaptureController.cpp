#include "VideoCaptureController.h"

VideoCaptureController::VideoCaptureController(VideoCaptureManager* videoCaptureManager, VideoResizerFactory* videoResizerFactory, WindowSourceManager* windowSourceManager, VideoSettingsManager* videoSettingsManager, KeyboardListener* keyboardListener)
{
	_videoCaptureManager = videoCaptureManager;
	_videoResizerFactory = videoResizerFactory;
	_windowSourceManager = windowSourceManager;
	_videoSettingsManager = videoSettingsManager;
	_keyboardListener = keyboardListener;
	_eventDispatcher.addEntry(videoResizerFactory->getChangeEvent(), BIND(VideoCaptureController, onResizerChanged, this));
	_eventDispatcher.addEntry(windowSourceManager->getChangeEvent(), BIND(VideoCaptureController, onSourceChanged, this));
	_eventDispatcher.addEntry(keyboardListener->getRefreshEvent(), BIND(VideoCaptureController, onRefreshHotkeyPressed, this));
	_eventDispatcher.start();
	LogUtil::logDebug(L"VideoCaptureController: Started on thread %i.", _eventDispatcher.getThreadId());
}

VideoCaptureController::~VideoCaptureController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"VideoCaptureController: Stopped.");
}

void VideoCaptureController::onSourceChanged()
{
	LogUtil::logInfo(L"VideoCaptureController: Window source changed.");
	VideoSettings settings = _videoSettingsManager->getSettings();
	if (settings.doResize && settings.keepRatio)
	{
		Vector size = _windowSourceManager->getWindowSize();
		settings.width = size.x;
		settings.height = size.y;
		if (_videoSettingsManager->setSettings(settings))
		{
			LogUtil::logInfo(L"VideoCaptureController: Settings changed to the window size.");
		}
	}
	updateCapture();
}

void VideoCaptureController::onResizerChanged()
{
	LogUtil::logInfo(L"VideoCaptureController: Window source changed.");
	updateCapture();
}

void VideoCaptureController::onRefreshHotkeyPressed()
{
	LogUtil::logInfo(L"VideoCaptureController: Refresh hotkey pressed.");
	updateCapture();
}

void VideoCaptureController::updateCapture()
{
	LogUtil::logInfo(L"VideoCaptureController: Updating capture.");
	_videoCaptureManager->reset();
	VideoCapture* capture = _windowSourceManager->createCapture();
	capture = _videoResizerFactory->createResizer(capture);
	_videoCaptureManager->setCapture(capture);
}
