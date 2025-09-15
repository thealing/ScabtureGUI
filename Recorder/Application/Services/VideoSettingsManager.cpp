#include "VideoSettingsManager.h"

VideoSettingsManager::VideoSettingsManager() : SettingsManager(L"Video Settings")
{
	init();
}

VideoSettings VideoSettingsManager::getDefault() const
{
	VideoSettings settings = {};
	settings.showCursor = true;
	settings.frameRate = 60;
	settings.bitRate = 16000;
	settings.width = 640;
	settings.height = 480;
	settings.encodeFormat = EncodeFormatNV12;
	settings.resizeMode = ResizeModeLetterbox;
	return settings;
}

void VideoSettingsManager::validate(VideoSettings& settings) const
{
	if (settings.windowCaptureMethod < 0 || settings.windowCaptureMethod >= WindowCaptureMethodCount)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid window capture method %i.", settings.windowCaptureMethod);
		settings.windowCaptureMethod = WindowCaptureMethodDefault;
	}
	if (settings.screenCaptureMethod < 0 || settings.screenCaptureMethod >= ScreenCaptureMethodCount)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid screen capture method %i.", settings.screenCaptureMethod);
		settings.screenCaptureMethod = ScreenCaptureMethodDefault;
	}
	if (settings.encodeFormat < 0 || settings.encodeFormat >= EncodeFormatCount)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid encode format %i.", settings.encodeFormat);
		settings.encodeFormat = EncodeFormatIYUV;
	}
	if (settings.resizeMode < 0 || settings.resizeMode >= ResizeModeCount)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid resize mode %i.", settings.resizeMode);
		settings.resizeMode = ResizeModeStretch;
	}
	if (settings.frameRate < 1 || settings.frameRate > 9999)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid framerate %i.", settings.frameRate);
		settings.frameRate = clamp(settings.frameRate, 1, 9999);
	}
	if (settings.bitRate < 100 || settings.bitRate > 250000)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid bitrate %i.", settings.bitRate);
		settings.bitRate = clamp(settings.bitRate, 100, 250000);
	}
	if (settings.width < 0 || settings.width > 5000 || settings.width % 2 != 0)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid width %i.", settings.width);
		settings.width = clamp(settings.width, 0, 5000);
		settings.width += settings.width % 2;
	}
	if (settings.height < 0 || settings.height > 5000 || settings.height % 2 != 0)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid height %i.", settings.height);
		settings.height = clamp(settings.height, 0, 5000);
		settings.height += settings.height % 2;
	}
}
