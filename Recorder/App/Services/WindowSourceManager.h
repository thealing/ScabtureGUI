#pragma once

class WindowSourceManager : NonCopyable
{
public:

	WindowSourceManager();

	const Event* getChangeEvent();

	bool setSettings(const WindowSourceSettings& settings);

	bool selectSource(VideoSource source);

	Vector getWindowSize() const;

	VideoCapture* createCapture() const;

private:

	mutable ReadWriteLock _lock;

	WindowSourceSettings _settings;
	WindowSource _source;
	LatchEvent _settingsInitEvent;
	LatchEvent _sourceInitEvent;
	EventPool _changeEventPool;
};

