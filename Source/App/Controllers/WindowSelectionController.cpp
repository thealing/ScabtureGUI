#include "WindowSelectionController.h"

WindowSelectionController::WindowSelectionController(MainWindow* mainWindow, VideoSourceManager* videoSourceManager, WindowSourceManager* windowSourceManager)
{
	_mainWindow = mainWindow;
	_videoSourceManager = videoSourceManager;
	_windowSourceManager = windowSourceManager;
	_eventDispatcher.addEntry(videoSourceManager->getSelectionEvent(), BIND(WindowSelectionController, onSelection, this));
	_eventDispatcher.start(mainWindow);
	LogUtil::logDebug(L"WindowSelectionController: Started on thread %i.", _eventDispatcher.getThreadId());
}

WindowSelectionController::~WindowSelectionController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"WindowSelectionController: Stopped.");
}

void WindowSelectionController::onSelection()
{
	VideoSource source = _videoSourceManager->getSource();
	bool selected = false;
	if (source == VideoSourceFullscreen)
	{
		selected = _windowSourceManager->selectSource(source);
	}
	else
	{
		_mainWindow->hide();
		selected = _windowSourceManager->selectSource(source);
		_mainWindow->show();
		_mainWindow->activate();
	}
	if (selected)
	{
		LogUtil::logInfo(L"WindowSelectionController: Successfully selected source %i.", source);
	}
	else
	{
		LogUtil::logInfo(L"WindowSelectionController: Failed to select source %i.", source);
		_videoSourceManager->selectSource(VideoSourceFullscreen);
	}
}
