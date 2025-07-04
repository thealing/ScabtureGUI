#include "VideoCaptureController.h"

VideoCaptureController::VideoCaptureController(VideoCaptureManager* videoCaptureManager, VideoCaptureFactory* videoCaptureFactory, VideoResizerFactory* videoResizerFactory, VideoSourceManager* videoSourceManager, VideoSettingsManager* videoSettingsManager, KeyboardListener* keyboardListener)
{
	_videoCaptureManager = videoCaptureManager;
	_videoCaptureFactory = videoCaptureFactory;
	_videoResizerFactory = videoResizerFactory;
	_videoSourceManager = videoSourceManager;
	_videoSettingsManager = videoSettingsManager;
	_keyboardListener = keyboardListener;
	_eventDispatcher.addEntry(videoCaptureManager->getErrorEvent(), BIND(VideoCaptureController, onCaptureFailed, this));
	_eventDispatcher.addEntry(videoCaptureFactory->getChangeEvent(), BIND(VideoCaptureController, onCaptureChanged, this));
	_eventDispatcher.addEntry(videoResizerFactory->getChangeEvent(), BIND(VideoCaptureController, onResizerChanged, this));
	_eventDispatcher.addEntry(keyboardListener->getRefreshEvent(), BIND(VideoCaptureController, onRefreshHotkeyPressed, this));
	_eventDispatcher.start();
	LogUtil::logDebug(L"VideoCaptureController: Started on thread %i.", _eventDispatcher.getThreadId());
}

VideoCaptureController::~VideoCaptureController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"VideoCaptureController: Stopped.");
}

void VideoCaptureController::onCaptureFailed()
{
	LogUtil::logInfo(L"VideoCaptureController: Video capture failed.");
	_videoSourceManager->selectSource(VideoSourceFullscreen);
}

void VideoCaptureController::onCaptureChanged()
{
	LogUtil::logInfo(L"VideoCaptureController: Video capture changed.");
	updateCapture();
}

void VideoCaptureController::onResizerChanged()
{
	LogUtil::logInfo(L"VideoCaptureController: Video resizer changed.");
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
	VideoCapture* capture = _videoCaptureFactory->createCapture();
	capture = _videoResizerFactory->createResizer(capture);
	_videoCaptureManager->setCapture(capture);
	MessageBeep(MB_OK);
}
