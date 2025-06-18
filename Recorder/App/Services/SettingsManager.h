#pragma once

template<class Settings>
class SettingsManager : NonCopyable
{
public:

	SettingsManager(const wchar_t* name);

	const Event* getChangeEvent();

	bool setSettings(const Settings& settings);

	Settings getSettings() const;

	virtual ~SettingsManager();

protected:

	void init();

	virtual Settings getDefault() const = 0;

	virtual void validate(Settings& settings) const = 0;

private:

	const wchar_t* _name;
	Settings _settings;
	EventPool _changeEventPool;
};
