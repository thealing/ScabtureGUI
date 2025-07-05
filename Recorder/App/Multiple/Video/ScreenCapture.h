#pragma once

class ScreenCapture : public FrameEmitter<VideoCapture>
{
public:

	ScreenCapture();

	virtual const Buffer* getBuffer() const override;

protected:

	void setCapture(Capture* capture);

	void start(int frameRate);

private:

	void onTimer();

private:

	UniquePointer<Capture> _capture;
	UniquePointer<Timer> _timer;
};

