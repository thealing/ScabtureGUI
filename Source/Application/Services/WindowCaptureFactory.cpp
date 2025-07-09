#include "WindowCaptureFactory.h"

WindowCaptureFactory::WindowCaptureFactory()
{
}

const Event* WindowCaptureFactory::getChangeEvent()
{
	return _settingsManager.getChangeEvent();
}

bool WindowCaptureFactory::setSettings(const WindowCaptureSettings& settings)
{
	return _settingsManager.setSettings(settings);
}

VideoCapture* WindowCaptureFactory::createCapture(HWND window, RECT rect) const
{
	POINT position = RectUtil::getRectPosition(rect);
	SIZE size = RectUtil::getRectSize(rect);
	WindowCaptureSettings settings = _settingsManager.getSettings();
	WindowCapture* capture = NULL;
	switch (settings.method)
	{
		case WindowCaptureMethodBitBlt:
		{
			capture = new BitBltCapture(window, position, size);
			break;
		}
		case WindowCaptureMethodPrintWindow:
		{
			capture = new DwmPrintWindowCapture(window);
			break;
		}
		case WindowCaptureMethodSharedSurface:
		{
			capture = new DwmSharedSurfaceCapture(window, position, size);
			break;
		}
	}
	if (settings.showCursor)
	{
		MouseOverlay* overlay = new MouseOverlay(window, position);
		capture->addOverlay(overlay);
	}
	capture->start(settings.frameRate);
	return capture;
}
