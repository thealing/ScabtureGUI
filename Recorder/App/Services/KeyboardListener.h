#pragma once

class KeyboardListener : NonCopyable
{
public:

	KeyboardListener();

	~KeyboardListener();

	bool setSettings(const KeyboardSettings& settings);

	const Event* getStartEvent() const;

	const Event* getStopEvent() const;

	const Event* getPauseEvent() const;

	const Event* getResumeEvent() const;

	const Event* getSnapshotEvent() const;

	const Event* getRefreshEvent() const;

private:

	void handleInput(const Hotkey& hotkey);

private:

	KeyboardSettings _settings;
	HHOOK _hook;
	Event _startEvent;
	Event _stopEvent;
	Event _pauseEvent;
	Event _resumeEvent;
	Event _snapshotEvent;
	Event _refreshEvent;

private:

	static LRESULT CALLBACK hookProc(int code, WPARAM wParam, LPARAM lParam);
};

