#include "SettingsManager.h"

template<class Settings>
SettingsManager<Settings>::SettingsManager(const wchar_t* name)
{
	_name = name;
	_settings = {};
}

template<class Settings>
const Event* SettingsManager<Settings>::getChangeEvent()
{
	return _changeEventPool.getEvent();
}

template<class Settings>
bool SettingsManager<Settings>::setSettings(const Settings& settings)
{
	// Must always signal a change for the first setting!
	if (!_initEvent.set())
	{
		if (MemoryUtil::areEqual(_settings, settings))
		{
			return false;
		}
	}
	_settings = settings;
	validate(_settings);
	SaveUtil::saveSettings(_name, &_settings);
	_changeEventPool.setEvents();
	return true;
}

template<class Settings>
Settings SettingsManager<Settings>::getSettings() const
{
	return _settings;
}

template<class Settings>
void SettingsManager<Settings>::init()
{
	Settings settings = getDefault();
	SaveUtil::loadSettings(_name, &settings);
	setSettings(settings);
}
