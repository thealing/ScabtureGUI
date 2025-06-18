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
	bool init = _initEvent.set();
	bool unchanged = MemoryUtil::areEqual(_settings, settings);
	_settings = settings;
	if (init)
	{
		return true;
	}
	if (unchanged)
	{
		return false;
	}
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
