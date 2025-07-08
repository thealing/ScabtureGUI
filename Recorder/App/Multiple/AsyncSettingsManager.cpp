#include "AsyncSettingsManager.h"

template<class Settings>
AsyncSettingsManager<Settings>::AsyncSettingsManager()
{
	_settings = {};
}

template<class Settings>
const Event* AsyncSettingsManager<Settings>::getChangeEvent()
{
	return _updateEventPool.getEvent();
}

template<class Settings>
bool AsyncSettingsManager<Settings>::setSettings(const Settings& settings)
{
	ExclusiveLockHolder holder(&_lock);
	if (_initEvent.set())
	{
		_settings = settings;
		return true;
	}
	if (MemoryUtil::areEqual(_settings, settings))
	{
		return false;
	}
	_settings = settings;
	_updateEventPool.setEvents();
	return true;
}

template<class Settings>
Settings AsyncSettingsManager<Settings>::getSettings() const
{
	_initEvent.wait();
	ExclusiveLockHolder holder(&_lock);
	_updateEventPool.resetEvents();
	return _settings;
}
