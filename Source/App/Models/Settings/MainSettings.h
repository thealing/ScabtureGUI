#pragma once

struct MainSettings
{
	bool stayOnTop;
	WindowVisibility windowVisibility;
	bool highQualityPreview;
	bool disablePreviewWhileRecording;
	bool stopOnVideoError;
	bool stopOnAudioError;
	bool askToPlayTheRecording;
	bool useHardwareEncoder;
	bool lowLatencyMode;
	Hotkey startHotkey;
	Hotkey stopHotkey;
	Hotkey pauseHotkey;
	Hotkey resumeHotkey;
	Hotkey snapshotHotkey;
	Hotkey refreshHotkey;
	LogMode logMode;
};
