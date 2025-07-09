#include "SaveUtil.h"

template<class Settings>
bool SaveUtil::loadSettings(const wchar_t* name, Settings* settings)
{
	SaveManager& saveManager = SaveManager::getInstance();
	return saveManager.loadData(name, sizeof(Settings), settings);
}

template<class Settings>
bool SaveUtil::saveSettings(const wchar_t* name, const Settings* settings)
{
	SaveManager& saveManager = SaveManager::getInstance();
	return saveManager.saveData(name, sizeof(Settings), settings);
}
