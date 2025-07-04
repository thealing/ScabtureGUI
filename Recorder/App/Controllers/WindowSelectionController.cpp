#include "WindowSelectionController.h"

WindowSelectionController::WindowSelectionController(MainWindow* mainWindow, VideoSourceManager* videoSourceManager, VideoCaptureFactory* videoCaptureFactory)
{
	_mainWindow = mainWindow;
	_videoSourceManager = videoSourceManager;
	_videoCaptureFactory = videoCaptureFactory;
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
		_videoCaptureFactory->setFullscreenSource();
		selected = true;
	}
	else
	{
		_mainWindow->hide();
		if (source == VideoSourceRectangle)
		{
			RectangleSelector selector;
			selector.run();
			if (selector.hasSelectedRect())
			{
				RECT rect = selector.getSelectedRect();
				_videoCaptureFactory->setRectangleSource(rect);
				selected = true;
			}
		}
		if (source == VideoSourceWindow)
		{
			WindowSelector selector;
			selector.run();
			if (selector.getSelectedWindow())
			{
				HWND window = selector.getSelectedWindow();
				_videoCaptureFactory->setWindowSource(window);
				selected = true;
			}
		}
		_mainWindow->show();
		_mainWindow->activate();
	}
	if (selected)
	{
		LogUtil::logInfo(L"WindowSelectionController: Successfully selected source %i.", source);
	}
	else
	{
		LogUtil::logWarning(L"WindowSelectionController: Failed to select source %i.", source);
		_videoSourceManager->selectSource(VideoSourceFullscreen);
	}
}
