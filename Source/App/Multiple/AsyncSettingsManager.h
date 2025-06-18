#pragma once

template<class Settings>
class AsyncSettingsManager
{
public:

	AsyncSettingsManager();

	const Event* getChangeEvent();

	bool setSettings(const Settings& settings);

	Settings getSettings() const;

private:

	mutable ExclusiveLock _lock;
	mutable EventPool _updateEventPool;

	LatchEvent _initEvent;
	Settings _settings;
};
