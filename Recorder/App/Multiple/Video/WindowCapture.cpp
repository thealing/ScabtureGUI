#include "WindowCapture.h"

WindowCapture::WindowCapture(const WindowCaptureSettings& settings, const WindowSource& source)
{
	int width = RectUtil::getRectWidth(source.rect);
	int height = RectUtil::getRectHeight(source.rect);
	_buffer = new Buffer(width, height);
	CaptureSource captureSource = {};
	captureSource.window = source.window;
	captureSource.rect = source.rect;
	captureSource.client = source.client;
	captureSource.width = _buffer->getWidth();
	captureSource.height = _buffer->getHeight();
	captureSource.stride = _buffer->getStride();
	if (settings.showCursor)
	{
		Capture* capture = createCapture(captureSource, settings.method);
		_capture = new MouseCapture(captureSource, capture, settings.drawCursor);
	}
	else
	{
		_capture = createCapture(captureSource, settings.method);
	}
	_timer = new Timer(0, 1.0 / settings.frameRate, BIND(WindowCapture, onTimer, this));
}

WindowCapture::~WindowCapture()
{
}

const Buffer* WindowCapture::getBuffer() const
{
	return _buffer;
}

void WindowCapture::onTimer()
{
	if (_capture->getFrame(_buffer))
	{
		signalFrame();
	}
}

Capture* WindowCapture::createCapture(const CaptureSource& source, CaptureMethod method)
{
	switch (method)
	{
		case CaptureMethodBitBltGetDIBits:
		{
			return new BitBltGetDIBitsCapture(source);
		}
		default:
		{
			return new BitBltGetDIBitsCapture(source);
		}
	}
}
