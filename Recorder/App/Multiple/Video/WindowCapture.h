#pragma once

class WindowCapture : public FrameEmitter<VideoCapture>
{
public:

	WindowCapture(HWND window, int frameRate, bool showCursor);

	virtual const Buffer* getBuffer() const override;

private:

	void onTimer();

private:

	HWND _window;
	UniquePointer<Capture> _capture;
	UniquePointer<Timer> _timer;
};

