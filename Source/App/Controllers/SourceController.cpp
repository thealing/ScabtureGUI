#include "SourceController.h"

SourceController::SourceController(SourcePanel* sourcePanel, VideoSourceManager* videoSourceManager, AudioSourceManager* audioSourceManager)
{
	_sourcePanel = sourcePanel;
	_videoSourceManager = videoSourceManager;
	_audioSourceManager = audioSourceManager;
	_eventDispatcher.addEntry(sourcePanel->getVideoChangeEvent(), BIND(SourceController, onVideoSourceChanged, this));
	_eventDispatcher.addEntry(sourcePanel->getAudioChangeEvent(), BIND(SourceController, onAudioSourceChanged, this));
	_eventDispatcher.addEntry(videoSourceManager->getChangeEvent(), BIND(SourceController, updateVideoSource, this));
	_eventDispatcher.addEntry(audioSourceManager->getChangeEvent(), BIND(SourceController, updateAudioSource, this));
	_eventDispatcher.start(sourcePanel);
	LogUtil::logDebug(L"SourceController: Started on thread %i.", _eventDispatcher.getThreadId());
}

SourceController::~SourceController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"SourceController: Stopped.");
}

void SourceController::onVideoSourceChanged()
{
	VideoSource source = (VideoSource)_sourcePanel->getVideoSource();
	LogUtil::logInfo(L"SourceController: Selecting video source %i.", source);
	bool selected = false;
	if (source == VideoSourceFullscreen)
	{
		// TODO: Select display?
		HWND window = GetDesktopWindow();
		_videoSourceManager->setFullscreenSource(window);
		selected = true;
	}
	else
	{
		Window* mainWindow = _sourcePanel->getTopLevelParent();
		mainWindow->hide();
		if (source == VideoSourceRectangle)
		{
			RectangleSelector selector;
			selector.run();
			if (selector.hasSelectedRect())
			{
				HWND window = GetDesktopWindow();
				RECT rect = selector.getSelectedRect();
				_videoSourceManager->setRectangleSource(window, rect);
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
				_videoSourceManager->setWindowSource(window);
				selected = true;
			}
		}
		mainWindow->show();
		mainWindow->activate();
	}
	if (selected)
	{
		LogUtil::logInfo(L"SourceController: Selected video source %i.", source);
	}
	else
	{
		LogUtil::logWarning(L"SourceController: Failed to select video source %i.", source);
		VideoSource source = _videoSourceManager->getSource();
		_sourcePanel->setVideoSource(source);
	}
}

void SourceController::onAudioSourceChanged()
{
	AudioSource source = (AudioSource)_sourcePanel->getAudioSource();
	LogUtil::logInfo(L"SourceController: Selected audio source %i.", source);
	_audioSourceManager->setSource(source);
}

void SourceController::updateVideoSource()
{
	VideoSource source = _videoSourceManager->getSource();
	LogUtil::logInfo(L"SourceController: Video source changed to %i.", source);
	_sourcePanel->setVideoSource(source);
}

void SourceController::updateAudioSource()
{
	AudioSource source = _audioSourceManager->getSource();
	LogUtil::logInfo(L"SourceController: Audio source changed to %i.", source);
	_sourcePanel->setAudioSource(source);
}
