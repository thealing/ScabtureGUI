#include "MainSettingsDialog.h"

MainSettingsDialog::MainSettingsDialog()
{
}

MainSettingsDialog::~MainSettingsDialog()
{
}

DialogWindow* MainSettingsDialog::createWindow(Window* parent)
{
	return new DialogWindow(parent, L"Settings", 450, 26, 10, 6);
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
	window->addCheckBox(L"Stop recording when the source window changes", 16, &settings->stopWhenTheWindowChanges);
	window->addCheckBox(L"Stop recording when an audio device changes", 16, &settings->stopWhenTheAudioDeviceChanges);
	window->addCheckBox(L"Beep before the recording starts", 16, &settings->beepWhenTheRecordingStarts);
	window->addCheckBox(L"Beep after the recording ends", 16, &settings->beepWhenTheRecordingStops);
	window->addCheckBox(L"Ask to play recording when finished", 16, &settings->askToPlayTheSavedRecording);
	window->addSeparator();
	window->addCheckBox(L"High quality preview", 16, &settings->highQualityPreview);
	window->addCheckBox(L"Disable preview while recording", 16, &settings->disablePreview);
	window->addSeparator();
	window->addCheckBox(L"Use hardware encoder", 16, &settings->useHardwareEncoder);
	window->addCheckBox(L"Low latency mode", 16, &settings->lowLatencyEncoder);
	window->addCheckBox(L"Disable throttling", 16, &settings->disableThrottling);
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
	window->addComboBox(L"Logging (requires restart)", 160, (int*)&settings->logMode, logModeNames, ARRAYSIZE(logModeNames));
}
