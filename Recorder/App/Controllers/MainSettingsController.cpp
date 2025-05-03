#include "MainSettingsController.h"

MainSettingsController::MainSettingsController(SettingsPanel* settingsPanel, MainSettingsDialog* mainSettingsDialog, MainSettingsManager* mainSettingsManager) : _eventDispatcher(settingsPanel)
{
	_settingsPanel = settingsPanel;
	_mainSettingsDialog = mainSettingsDialog;
	_mainSettingsManager = mainSettingsManager;
	_eventDispatcher.addEntry(settingsPanel->getSettingsClickEvent(), BIND(MainSettingsController, onButtonClicked, this));
	_eventDispatcher.start();
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
	Callback callback = BIND(MainSettingsController, onDialogClosed, this);
	_mainSettingsDialog->show(parent, settings, callback);
}

void MainSettingsController::onDialogClosed()
{
	const MainSettings* settings = _mainSettingsDialog->getSavedSettings();
	if (settings != NULL)
	{
		LogUtil::logInfo(L"MainSettingsController: Settings saved.");
		_mainSettingsManager->setSettings(*settings);
	}
	else
	{
		LogUtil::logInfo(L"MainSettingsController: Settings cancelled.");
	}
	_settingsPanel->setEnabled(true);
}
