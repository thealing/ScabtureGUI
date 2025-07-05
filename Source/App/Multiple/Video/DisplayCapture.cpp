#include "DisplayCapture.h"

DisplayCapture::DisplayCapture(RECT rect, int frameRate, bool showCursor)
{
	HWND window = GetDesktopWindow();
	Capture* capture = new BitBltGetBitmapBitsCapture(window, rect);
	if (showCursor)
	{
		POINT offset = { rect.left, rect.top };
		Overlay* mouseOverlay = new MouseOverlay(window, offset);
		capture->addOverlay(mouseOverlay);
	}
	setCapture(capture);
	start(frameRate);
}
