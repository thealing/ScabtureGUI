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
		case WindowCaptureMethodBitBltGetBitmapBits:
		{
			capture = new BitBltGetBitmapBitsCapture(window, position, size);
			break;
		}
		case WindowCaptureMethodBitBltGetDIBits:
		{
			capture = new BitBltGetDIBitsCapture(window, position, size);
			break;
		}
		case WindowCaptureMethodBitBltDIBSection:
		{
			capture = new BitBltDIBSectionCapture(window, position, size);
			break;
		}
		case WindowCaptureMethodPrintWindowGetBitmapBits:
		{
			capture = new PrintWindowGetBitmapBitsCapture(window);
			break;
		}
		case WindowCaptureMethodPrintWindowGetDIBits:
		{
			capture = new PrintWindowGetDIBitsCapture(window);
			break;
		}
		case WindowCaptureMethodPrintWindowDIBSection:
		{
			capture = new PrintWindowDIBSectionCapture(window);
			break;
		}
		case WindowCaptureMethodDwmGetDxSharedSurface:
		{
			capture = new DwmGetDxSharedSurfaceCapture(window, position, size);
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
