#include "SettingsManager.h"

template<class Settings>
SettingsManager<Settings>::SettingsManager(const wchar_t* name) : _name(name), _settings()
{
}

template<class Settings>
bool SettingsManager<Settings>::setSettings(const Settings& settings)
{
	if (MemoryUtil::areEqual(_settings, settings))
	{
		return false;
	}
	_settings = settings;
	validate(_settings);
	_provider.save(_name, &_settings);
	_changeEventPool.setEvents();
	return true;
}

template<class Settings>
Settings SettingsManager<Settings>::getSettings() const
{
	return _settings;
}

template<class Settings>
const Event* SettingsManager<Settings>::getChangeEvent() const
{
	return _changeEventPool.getEvent();
}

template<class Settings>
SettingsManager<Settings>::~SettingsManager()
{
}

template<class Settings>
void SettingsManager<Settings>::init()
{
	Settings settings = {};
	if (_provider.load(_name, &settings))
	{
		LogUtil::logInfo(L"Successfully loaded \"%ls\".", _name);
	}
	else
	{
		LogUtil::logInfo(L"Using default values for \"%ls\".", _name);
		settings = getDefault();
	}
	setSettings(settings);
}
