#include "SaveManager.h"

#define REGISTRY_KEY_PATH L"SOFTWARE\\Scabture2"

SaveManager& SaveManager::getInstance()
{
	static SaveManager instance;
	return instance;
}

bool SaveManager::loadData(const wchar_t* name, int count, void* data)
{
	DWORD size = count;
	LSTATUS result = RegQueryValueEx(_key, name, 0, NULL, (LPBYTE)data, &size);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"SaveManager: Failed to query registry value \"%ls\" (error %i).", name, result);
		return false;
	}
	return true;
}

bool SaveManager::saveData(const wchar_t* name, int count, const void* data)
{
	DWORD size = count;
	LSTATUS result = RegSetValueEx(_key, name, 0, REG_BINARY, (LPBYTE)data, size);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"SaveManager: Failed to set registry value \"%ls\" (error %i).", name, result);
		return false;
	}
	return true;
}

SaveManager::SaveManager()
{
	_key = NULL;
	DWORD action = 0;
	LSTATUS result = RegCreateKeyEx(HKEY_CURRENT_USER, REGISTRY_KEY_PATH, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &_key, &action);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logError(L"SaveManager: Failed to access registry key \"%ls\" (error %i).", REGISTRY_KEY_PATH, result);
	}
}

SaveManager::~SaveManager()
{
	LSTATUS result = RegCloseKey(_key);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"SaveManager: Failed to close registry key \"%ls\" (error %i).", REGISTRY_KEY_PATH, result);
	}
}
