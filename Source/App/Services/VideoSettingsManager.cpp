#include "VideoSettingsManager.h"

VideoSettingsManager::VideoSettingsManager() : SettingsManager(L"Video Settings")
{
	init();
}

VideoSettings VideoSettingsManager::getDefault() const
{
	VideoSettings settings = {};
	settings.windowArea = WindowAreaVisible;
	settings.captureMethod = CaptureMethodDefault;
	settings.showCursor = true;
	settings.drawCursor = false;
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
	if (settings.windowArea < 0 || settings.windowArea >= WindowAreaCount)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid window area %i.", settings.windowArea);
		settings.windowArea = WindowAreaDefault;
	}
	if (settings.captureMethod < 0 || settings.captureMethod >= CaptureMethodCount)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid capture method %i.", settings.captureMethod);
		settings.captureMethod = CaptureMethodDefault;
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
	if (settings.frameRate < 1 || settings.frameRate > 150)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid framerate %i.", settings.frameRate);
		settings.frameRate = clamp(settings.frameRate, 1, 150);
	}
	if (settings.bitRate < 100 || settings.bitRate > 250000)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid bitrate %i.", settings.bitRate);
		settings.bitRate = clamp(settings.bitRate, 100, 250000);
	}
	if (settings.width < 1 || settings.width > 5000 || settings.width % 2 != 0)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid width %i.", settings.width);
		settings.width = clamp(settings.width, 1, 5000);
		settings.width += settings.width % 2;
	}
	if (settings.height < 1 || settings.height > 5000 || settings.height % 2 != 0)
	{
		LogUtil::logWarning(L"VideoSettingsManager: Found invalid height %i.", settings.height);
		settings.height = clamp(settings.height, 1, 5000);
		settings.height += settings.height % 2;
	}
}
