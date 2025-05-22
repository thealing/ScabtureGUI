#include "Capture.h"

Capture::~Capture()
{
}

void Capture::addOverlay(Overlay* overlay)
{
	_overlays.store(overlay);
}

void Capture::drawOverlays(uint32_t* pixels, int width, int height, int stride)
{
	for (Overlay* overlay : _overlays)
	{
		overlay->draw(pixels, width, height, stride);
	}
}
