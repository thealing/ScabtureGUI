#pragma once

template<class Settings>
class AsyncSettingsManager
{
public:

	AsyncSettingsManager();

	bool setSettings(const Settings& settings);

	Settings getSettings() const;

	const Event* getChangeEvent() const;

private:

	mutable ExclusiveLock _lock;
	mutable EventPool _updateEventPool;

	Settings _settings;
	LatchEvent _initEvent;
};
