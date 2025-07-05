#include "MainSettingsController.h"

MainSettingsController::MainSettingsController(SettingsPanel* settingsPanel, MainSettingsDialog* mainSettingsDialog, MainSettingsManager* mainSettingsManager)
{
	_settingsPanel = settingsPanel;
	_mainSettingsDialog = mainSettingsDialog;
	_mainSettingsManager = mainSettingsManager;
	_eventDispatcher.addEntry(settingsPanel->getSettingsClickEvent(), BIND(MainSettingsController, onButtonClicked, this));
	_eventDispatcher.start(settingsPanel);
	LogUtil::logDebug(L"MainSettingsController: Started on thread %i.", _eventDispatcher.getThreadId());
}

MainSettingsController::~MainSettingsController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"MainSettingsController: Stopped.");
}

void MainSettingsController::onButtonClicked()
{
	LogUtil::logInfo(L"MainSettingsController: Button clicked.");
	_settingsPanel->setEnabled(false);
	Window* parent = _settingsPanel->getTopLevelParent();
	MainSettings settings = _mainSettingsManager->getSettings();
	Callback callback = BIND(MainSettingsController, onSettingsChanged, this);
	_mainSettingsDialog->show(parent, settings, callback);
}

void MainSettingsController::onSettingsChanged()
{
	MainSettings settings = _mainSettingsDialog->getSettings();
	if (_mainSettingsManager->setSettings(settings))
	{
		LogUtil::logInfo(L"MainSettingsController: Settings changed.");
	}
	_settingsPanel->setEnabled(true);
}
