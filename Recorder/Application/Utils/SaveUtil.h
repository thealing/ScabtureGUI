#pragma once

class SaveUtil
{
public:

	template<class Settings>
	static bool loadSettings(const wchar_t* name, Settings* settings);

	template<class Settings>
	static bool saveSettings(const wchar_t* name, const Settings* settings);
};
