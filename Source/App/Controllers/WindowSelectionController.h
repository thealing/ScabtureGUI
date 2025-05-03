#pragma once

class WindowSelectionController : NonCopyable
{
public:

	WindowSelectionController(MainWindow* mainWindow, VideoSourceManager* videoSourceManager, WindowSourceManager* windowSourceManager);

	~WindowSelectionController();

private:

	void onSelection();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<MainWindow> _mainWindow;
	WeakPointer<VideoSourceManager> _videoSourceManager;
	WeakPointer<WindowSourceManager> _windowSourceManager;
};

