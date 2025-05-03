#include "SettingsProvider.h"

#define REGISTRY_KEY_PATH L"SOFTWARE\\Scabture2"

template<class Settings>
SettingsProvider<Settings>::SettingsProvider()
{
	_key = NULL;
	DWORD action = 0;
	LSTATUS result = RegCreateKeyEx(HKEY_CURRENT_USER, REGISTRY_KEY_PATH, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &_key, &action);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logError(L"Failed to access registry key \"%ls\" (error %i).", REGISTRY_KEY_PATH, result);
		return;
	}
}

template<class Settings>
SettingsProvider<Settings>::~SettingsProvider()
{
	LSTATUS result = RegCloseKey(_key);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"Failed to close registry key (error %i).", result);
		return;
	}
}

template<class Settings>
bool SettingsProvider<Settings>::load(const wchar_t* name, Settings* settings)
{
	DWORD size = sizeof(Settings);
	LSTATUS result = RegQueryValueEx(_key, name, 0, NULL, (LPBYTE)settings, &size);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"Failed to query registry value \"%ls\" (error %i).", name, result);
		return false;
	}
	return true;
}

template<class Settings>
bool SettingsProvider<Settings>::save(const wchar_t* name, const Settings* settings)
{
	DWORD size = sizeof(Settings);
	LSTATUS result = RegSetValueEx(_key, name, 0, REG_BINARY, (LPBYTE)settings, size);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"Failed to set registry value \"%ls\" (error %i).", name, result);
		return false;
	}
	return true;
}
