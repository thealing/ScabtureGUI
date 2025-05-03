#pragma once

class WindowSourceManager : NonCopyable
{
public:

	WindowSourceManager();

	bool setSettings(const WindowSourceSettings& settings);

	bool selectSource(VideoSource source);

	Vector getWindowSize() const;

	VideoCapture* createCapture() const;

	const Event* getChangeEvent() const;

private:

	WindowSourceSettings _settings;
	WindowSource _source;
	EventPool _changeEventPool;
};

