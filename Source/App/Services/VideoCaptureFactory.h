#pragma once

class VideoCaptureFactory : NonCopyable
{
public:

	VideoCaptureFactory();

	const Event* getChangeEvent();

	bool setSettings(const CaptureSettings& settings);

	void setFullscreenSource();

	void setRectangleSource(RECT rect);

	void setWindowSource(HWND window);

	VideoCapture* createCapture() const;

private:

	void setSource(HWND window, RECT rect);

private:

	mutable ReadWriteLock _lock;

	CaptureSettings _settings;
	HWND _sourceWindow;
	RECT _sourceRect;
	EventPool _changeEventPool;
};

