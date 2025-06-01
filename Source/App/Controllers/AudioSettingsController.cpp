#include "AudioSettingsController.h"

AudioSettingsController::AudioSettingsController(SourcePanel* sourcePanel, AudioSettingsDialog* audioSettingsDialog, AudioSettingsManager* audioSettingsManager)
{
	_sourcePanel = sourcePanel;
	_audioSettingsDialog = audioSettingsDialog;
	_audioSettingsManager = audioSettingsManager;
	_eventDispatcher.addEntry(sourcePanel->getAudioOptionsClickEvent(), BIND(AudioSettingsController, onButtonClicked, this));
	_eventDispatcher.start(sourcePanel);
	LogUtil::logDebug(L"AudioSettingsController: Started on thread %i.", _eventDispatcher.getThreadId());
}

AudioSettingsController::~AudioSettingsController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"AudioSettingsController: Stopped.");
}

void AudioSettingsController::onButtonClicked()
{
	LogUtil::logInfo(L"AudioSettingsController: Button clicked.");
	Window* parent = _sourcePanel->getTopLevelParent();
	AudioSettings settings = _audioSettingsManager->getSettings();
	Callback callback = BIND(AudioSettingsController, onDialogClosed, this);
	_audioSettingsDialog->show(parent, settings, callback);
}

void AudioSettingsController::onDialogClosed()
{
	const AudioSettings* settings = _audioSettingsDialog->getSavedSettings();
	if (settings != NULL)
	{
		LogUtil::logInfo(L"AudioSettingsController: Settings saved.");
		_audioSettingsManager->setSettings(*settings);
	}
	else
	{
		LogUtil::logInfo(L"AudioSettingsController: Settings cancelled.");
	}
}
