#include "SettingsDialog.h"

template<class Settings>
SettingsDialog<Settings>::SettingsDialog()
{
}

template<class Settings>
void SettingsDialog<Settings>::show(Window* parent, const Settings& settings, const Callback& callback)
{
	if (_window != NULL)
	{
		LogUtil::logWarning(L"SettingsDialog: Window is already visible.");
		return;
	}
	_callback = callback;
	_settings = settings;
	_oldSettings = settings;
	_window = createWindow(parent);
	_window->setConfirmCallback(BIND(SettingsDialog, onConfirmed, this));
	_window->setCancelCallback(BIND(SettingsDialog, onCancelled, this));
	_window->setChangeCallback(BIND(SettingsDialog, onChanged, this));
	createControls(_window, &_settings);
	_window->finalize();
}

template<class Settings>
Settings SettingsDialog<Settings>::getSettings() const
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
	_window = NULL;
	_callback.invoke();
}

template<class Settings>
void SettingsDialog<Settings>::onCancelled()
{
	assert(_window != NULL);
	_window = NULL;
	_settings = _oldSettings;
	_callback.invoke();
}

template<class Settings>
void SettingsDialog<Settings>::onChanged()
{
	assert(_window != NULL);
	_callback.invoke();
}
