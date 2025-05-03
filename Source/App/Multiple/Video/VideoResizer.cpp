#include "VideoResizer.h"

VideoResizer::VideoResizer(VideoCapture* source, Resizer* resizer, Buffer* buffer)
{
	_source = source;
	_resizer = resizer;
	_buffer = buffer;
	_eventDispatcher.addEntry(source->getFrameEvent(), BIND(VideoResizer, onFrame, this));
	_eventDispatcher.start();
}

VideoResizer::~VideoResizer()
{
	_eventDispatcher.stop();
}

const Buffer* VideoResizer::getBuffer() const
{
	return _buffer;
}

void VideoResizer::onFrame()
{
	const Buffer* inputBuffer = _source->getBuffer();
	const uint32_t* inputPixels = inputBuffer->beginReading();
	uint32_t* outputPixels = _buffer->beginWriting();
	_resizer->resize(inputPixels, outputPixels);
	_buffer->endWriting();
	inputBuffer->endReading();
	signalFrame();
}
