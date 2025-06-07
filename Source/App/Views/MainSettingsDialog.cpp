#include "MainSettingsDialog.h"

MainSettingsDialog::MainSettingsDialog()
{
}

MainSettingsDialog::~MainSettingsDialog()
{
}

DialogWindow* MainSettingsDialog::createWindow(Window* parent)
{
	return new DialogWindow(parent, L"Settings", 390, 26, 10, 5);
}

void MainSettingsDialog::createControls(DialogWindow* window, MainSettings* settings)
{
	window->addCheckBox(L"Stay on top", 16, &settings->stayOnTop);
	const wchar_t* windowVisibilityNames[WindowVisibilityCount] = {};
	windowVisibilityNames[WindowVisibilityNormal] = L"Normal";
	windowVisibilityNames[WindowVisibilityMinimized] = L"Minimized";
	windowVisibilityNames[WindowVisibilityHidden] = L"Hidden";
	window->addComboBox(L"Visibility during recording", 140, (int*)&settings->windowVisibility, windowVisibilityNames, ARRAYSIZE(windowVisibilityNames));
	window->addSeparator();
	window->addCheckBox(L"Stop recording if the video capture ends", 16, &settings->stopOnVideoError);
	window->addCheckBox(L"Stop recording if the audio capture ends", 16, &settings->stopOnAudioError);
	window->addSeparator();
	window->addCheckBox(L"High quality preview", 16, &settings->highQualityPreview);
	window->addCheckBox(L"Disable preview while recording", 16, &settings->disablePreviewWhileRecording);
	window->addSeparator();
	window->addCheckBox(L"Use hardware-accelerated encoders", 16, &settings->useHardwareEncoders);
	window->addCheckBox(L"Low latency mode", 16, &settings->lowLatencyMode);
	window->addSeparator();
	window->addCheckBox(L"Ask to play the recorded video", 16, &settings->askToPlayTheRecording);
	window->addSeparator();
	window->addHotkeyEdit(L"Start recording", 120, &settings->startHotkey);
	window->addHotkeyEdit(L"Stop recording", 120, &settings->stopHotkey);
	window->addHotkeyEdit(L"Pause recording", 120, &settings->pauseHotkey);
	window->addHotkeyEdit(L"Resume recording", 120, &settings->resumeHotkey);
	window->addHotkeyEdit(L"Take snapshot", 120, &settings->snapshotHotkey);
	window->addHotkeyEdit(L"Refresh capture", 120, &settings->refreshHotkey);
	window->addSeparator();
	const wchar_t* logModeNames[LogModeCount] = {};
	logModeNames[LogModeNone] = L"None";
	logModeNames[LogModeSingleFile] = L"Single file";
	logModeNames[LogModeNewFiles] = L"Time-stamped files";
	window->addComboBox(L"Logging output", 160, (int*)&settings->logMode, logModeNames, ARRAYSIZE(logModeNames));
}
