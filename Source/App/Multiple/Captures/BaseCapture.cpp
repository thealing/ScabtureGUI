#include "BaseCapture.h"

Buffer* BaseCapture::getBuffer()
{
    return _buffer;
}

void BaseCapture::addOverlay(Overlay* overlay)
{
	_overlays.store(overlay);
}

void BaseCapture::createBuffer(int width, int height)
{
	_buffer = new Buffer(width, height);
}

uint32_t* BaseCapture::beginFrame()
{
	return _buffer->beginWriting();
}

void BaseCapture::endFrame(bool result)
{
	if (result)
	{
		uint32_t* pixels = _buffer->getPixels();
		int width = _buffer->getWidth();
		int height = _buffer->getHeight();
		int stride = _buffer->getStride();
		for (Overlay* overlay : _overlays)
		{
			overlay->draw(pixels, width, height, stride);
		}
	}
	_buffer->endWriting();
}
