#include "MainSettingsManager.h"

MainSettingsManager::MainSettingsManager() : SettingsManager(L"Settings")
{
	init();
}

MainSettings MainSettingsManager::getDefault() const
{
	MainSettings settings = {};
	settings.windowVisibility = WindowVisibilityMinimized;
	settings.highQualityPreview = true;
	settings.disablePreviewDuringRecording = true;
	settings.askToPlayTheRecording = true;
	settings.useHardwareEncoders = true;
	settings.lowLatencyMode = true;
	return settings;
}

void MainSettingsManager::validate(MainSettings& settings) const
{
	if (settings.logMode < 0 || settings.logMode >= LogModeCount)
	{
		LogUtil::logWarning(L"MainSettingsManager: Found invalid log mode %i.", settings.logMode);
		settings.logMode = LogModeNone;
	}
	if (settings.windowVisibility < 0 || settings.windowVisibility >= WindowVisibilityCount)
	{
		LogUtil::logWarning(L"MainSettingsManager: Found invalid window visibility %i.", settings.windowVisibility);
		settings.windowVisibility = WindowVisibilityNormal;
	}
}
