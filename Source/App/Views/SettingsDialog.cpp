#include "SettingsDialog.h"

template<class Settings>
SettingsDialog<Settings>::SettingsDialog()
{
}

template<class Settings>
void SettingsDialog<Settings>::show(Window* parent, const Settings& settings, const Callback& callback)
{
	if ((_settings != NULL) ^ (_window != NULL))
	{
		LogUtil::logError(L"SettingsDialog: Inconsistent dialog state detected.");
		return;
	}
	if (_window != NULL)
	{
		LogUtil::logWarning(L"SettingsDialog: Window is already visible.");
		return;
	}
	_callback = callback;
	_settings = new Settings(settings);
	_window = createWindow(parent);
	createControls(_window, _settings);
	_window->setConfirmCallback(BIND(SettingsDialog, onConfirmed, this));
	_window->setCancelCallback(BIND(SettingsDialog, onCancelled, this));
	_window->finalize();
}

template<class Settings>
const Settings* SettingsDialog<Settings>::getSavedSettings() const
{
	return _settings;
}

template<class Settings>
SettingsDialog<Settings>::~SettingsDialog()
{
}

template<class Settings>
void SettingsDialog<Settings>::onConfirmed()
{
	assert(_window != NULL);
	assert(_settings != NULL);
	_window = NULL;
	_callback.invoke();
	_settings = NULL;
}

template<class Settings>
void SettingsDialog<Settings>::onCancelled()
{
	assert(_window != NULL);
	assert(_settings != NULL);
	_window = NULL;
	_settings = NULL;
	_callback.invoke();
}
