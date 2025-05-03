#pragma once

class WindowCapture : public VideoCapture
{
public:

	WindowCapture(const WindowCaptureSettings& settings, const WindowSource& source);

	virtual ~WindowCapture();

	virtual const Buffer* getBuffer() const override;

private:

	void onTimer();

private:

	UniquePointer<Buffer> _buffer;
	UniquePointer<Capture> _capture;
	UniquePointer<Timer> _timer;

private:

	static Capture* createCapture(const CaptureSource& source, CaptureMethod method);
};

