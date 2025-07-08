#pragma once

class ScreenCaptureFactory : NonCopyable
{
public:

	ScreenCaptureFactory();

	const Event* getChangeEvent();

	bool setSettings(const ScreenCaptureSettings& settings);

	VideoCapture* createCapture(HWND desktop, RECT rect) const;

private:

	AsyncSettingsManager<ScreenCaptureSettings> _settingsManager;
};

