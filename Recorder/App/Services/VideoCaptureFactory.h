#pragma once

class VideoCaptureFactory : NonCopyable
{
public:

	VideoCaptureFactory();

	const Event* getChangeEvent();

	bool setSettings(const CaptureSettings& settings);

	bool setFullscreenSource();

	bool setRectangleSource(RECT rect);

	bool setWindowSource(HWND window);

	VideoCapture* createCapture() const;

private:

	bool setSource(HWND window, RECT rect);

private:

	mutable ReadWriteLock _lock;

	CaptureSettings _settings;
	HWND _sourceWindow;
	RECT _sourceRect;
	EventPool _changeEventPool;
};

