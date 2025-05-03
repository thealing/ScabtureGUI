#pragma once

template<class Settings>
class SettingsProvider : NonCopyable
{
public:

	SettingsProvider();

	~SettingsProvider();

	bool load(const wchar_t* name, Settings* settings);

	bool save(const wchar_t* name, const Settings* settings);

private:

	HKEY _key;
};
