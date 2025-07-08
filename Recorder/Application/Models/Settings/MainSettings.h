#pragma once

struct MainSettings
{
	bool stayOnTop;
	WindowVisibility windowVisibility;
	bool highQualityPreview;
	bool disablePreviewDuringRecording;
	bool askToPlayTheRecording;
	bool useHardwareEncoders;
	bool lowLatencyMode;
	Hotkey startHotkey;
	Hotkey stopHotkey;
	Hotkey pauseHotkey;
	Hotkey resumeHotkey;
	Hotkey snapshotHotkey;
	Hotkey refreshHotkey;
	LogMode logMode;
};
