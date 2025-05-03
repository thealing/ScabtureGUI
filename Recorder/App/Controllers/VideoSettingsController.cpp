#include "VideoSettingsController.h"

VideoSettingsController::VideoSettingsController(SourcePanel* sourcePanel, VideoSettingsDialog* videoSettingsDialog, VideoSettingsManager* videoSettingsManager) : _eventDispatcher(sourcePanel)
{
	_sourcePanel = sourcePanel;
	_videoSettingsDialog = videoSettingsDialog;
	_videoSettingsManager = videoSettingsManager;
	_eventDispatcher.addEntry(sourcePanel->getVideoOptionsClickEvent(), BIND(VideoSettingsController, onButtonClicked, this));
	_eventDispatcher.start();
	LogUtil::logDebug(L"VideoSettingsController: Started on thread %i.", _eventDispatcher.getThreadId());
}

VideoSettingsController::~VideoSettingsController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"VideoSettingsController: Stopped.");
}

void VideoSettingsController::onButtonClicked()
{
	LogUtil::logInfo(L"VideoSettingsController: Button clicked.");
	Window* parent = _sourcePanel->getTopLevelParent();
	VideoSettings settings = _videoSettingsManager->getSettings();
	Callback callback = BIND(VideoSettingsController, onDialogClosed, this);
	_videoSettingsDialog->show(parent, settings, callback);
}

void VideoSettingsController::onDialogClosed()
{
	const VideoSettings* settings = _videoSettingsDialog->getSavedSettings();
	if (settings != NULL)
	{
		LogUtil::logInfo(L"VideoSettingsController: Settings saved.");
		_videoSettingsManager->setSettings(*settings);
	}
	else
	{
		LogUtil::logInfo(L"VideoSettingsController: Settings cancelled.");
	}
}
