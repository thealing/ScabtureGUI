#pragma once

struct MainSettings
{
	bool stayOnTop;
	WindowVisibility windowVisibility;
	bool highQualityPreview;
	bool disablePreviewWhileRecording;
	bool stopWhenTheWindowChanges;
	bool stopWhenTheAudioDeviceChanges;
	bool askToPlayTheSavedRecording;
	bool useHardwareEncoder;
	bool lowLatencyEncoder;
	Hotkey startHotkey;
	Hotkey stopHotkey;
	Hotkey pauseHotkey;
	Hotkey resumeHotkey;
	Hotkey snapshotHotkey;
	Hotkey refreshHotkey;
	LogMode logMode;
};
