#include "SaveManager.h"

#define REGISTRY_KEY_PATH L"SOFTWARE\\Scabture2"

SaveManager& SaveManager::getInstance()
{
	static SaveManager instance;
	return instance;
}

bool SaveManager::loadBytes(const wchar_t* name, int count, void* bytes)
{
	DWORD size = count;
	LSTATUS result = RegQueryValueEx(_key, name, 0, NULL, (LPBYTE)bytes, &size);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"SaveManager: Failed to query registry value \"%ls\" (error %i).", name, result);
		return false;
	}
	return true;
}

bool SaveManager::saveBytes(const wchar_t* name, int count, const void* bytes)
{
	DWORD size = count;
	LSTATUS result = RegSetValueEx(_key, name, 0, REG_BINARY, (LPBYTE)bytes, size);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"SaveManager: Failed to set registry value \"%ls\" (error %i).", name, result);
		return false;
	}
	return true;
}

bool SaveManager::loadString(const wchar_t* name, const wchar_t** string)
{
	DWORD type = 0;
	DWORD size = 0;
	LSTATUS result = RegQueryValueEx(_key, name, NULL, &type, NULL, &size);
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"SaveManager: Failed to query registry value \"%ls\" (error %i).", name, result);
		return false;
	}
	if (type != REG_SZ)
	{
		LogUtil::logWarning(L"SaveManager: The value \"%ls\" is not a string.", name);
		return false;
	}
	DWORD length = size / sizeof(wchar_t);
	if (length == 0)
	{
		LogUtil::logWarning(L"SaveManager: The value \"%ls\" has zero length.", name);
		return false;
	}
	wchar_t* data = new wchar_t[length];
	result = RegQueryValueEx(_key, name, NULL, NULL, (BYTE*)data, &size);
	data[length - 1] = '\0';
	if (result != ERROR_SUCCESS)
	{
		LogUtil::logWarning(L"SaveManager: Failed to query registry value \"%ls\" (error %i).", name, result);
		delete[] data;
		return false;
	}
	*string = data;
	return true;
}

bool SaveManager::saveString(const wchar_t* name, const wchar_t* string)
{
	DWORD length = (DWORD)wcslen(string) + 1;
	DWORD size = length * sizeof(wchar_t);
	LSTATUS result = RegSetValueEx(_key, name, 0, REG_SZ, (LPBYTE)string, size);
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
