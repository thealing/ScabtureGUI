#pragma once

class MainSettingsController : NonCopyable
{
public:

	MainSettingsController(SettingsPanel* settingsPanel, MainSettingsDialog* mainSettingsDialog, MainSettingsManager* mainSettingsManager);

	~MainSettingsController();

private:

	void onButtonClicked();

	void onDialogClosed();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<SettingsPanel> _settingsPanel;
	WeakPointer<MainSettingsDialog> _mainSettingsDialog;
	WeakPointer<MainSettingsManager> _mainSettingsManager;
};

