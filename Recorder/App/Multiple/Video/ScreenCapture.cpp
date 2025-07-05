#include "ScreenCapture.h"

ScreenCapture::ScreenCapture()
{
}

const Buffer* ScreenCapture::getBuffer() const
{
	return _capture->getBuffer();
}

void ScreenCapture::setCapture(Capture* capture)
{
	_capture = capture;
}

void ScreenCapture::start(int frameRate)
{
	if (_capture->getStatus())
	{
		_timer = new Timer(0, 1.0 / frameRate, BIND(ScreenCapture, onTimer, this));
	}
}

void ScreenCapture::onTimer()
{
	if (_capture->getFrame())
	{
		signalFrame();
	}
	if (!_capture->getStatus())
	{
		signalError();
	}
}
