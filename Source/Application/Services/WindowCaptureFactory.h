#pragma once

class WindowCaptureFactory : NonCopyable
{
public:

	WindowCaptureFactory();

	const Event* getChangeEvent();

	bool setSettings(const WindowCaptureSettings& settings);

	VideoCapture* createCapture(HWND window, RECT rect) const;

private:

	AsyncSettingsManager<WindowCaptureSettings> _settingsManager;
};

