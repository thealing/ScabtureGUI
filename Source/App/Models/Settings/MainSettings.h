#pragma once

struct MainSettings
{
	bool stayOnTop;
	WindowVisibility windowVisibility;
	bool highQualityPreview;
	bool disablePreview;
	bool stopWhenTheWindowChanges;
	bool stopWhenTheAudioDeviceChanges;
	bool beepWhenTheRecordingStarts;
	bool beepWhenTheRecordingStops;
	bool askToPlayTheSavedRecording;
	bool useHardwareEncoder;
	bool lowLatencyEncoder;
	bool disableThrottling;
	Hotkey startHotkey;
	Hotkey stopHotkey;
	Hotkey pauseHotkey;
	Hotkey resumeHotkey;
	Hotkey snapshotHotkey;
	Hotkey refreshHotkey;
	LogMode logMode;
};
