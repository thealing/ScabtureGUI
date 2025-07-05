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
	Callback callback = BIND(AudioSettingsController, onSettingsChanged, this);
	_audioSettingsDialog->show(parent, settings, callback);
}

void AudioSettingsController::onSettingsChanged()
{
	AudioSettings settings = _audioSettingsDialog->getSettings();
	if (_audioSettingsManager->setSettings(settings))
	{
		LogUtil::logInfo(L"AudioSettingsController: Settings changed.");
	}
}
