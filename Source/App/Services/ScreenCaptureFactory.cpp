#include "ScreenCaptureFactory.h"

ScreenCaptureFactory::ScreenCaptureFactory()
{
}

const Event* ScreenCaptureFactory::getChangeEvent()
{
	return _settingsManager.getChangeEvent();
}

bool ScreenCaptureFactory::setSettings(const ScreenCaptureSettings& settings)
{
	return _settingsManager.setSettings(settings);
}

VideoCapture* ScreenCaptureFactory::createCapture(HWND desktop, RECT rect) const
{
	POINT position = RectUtil::getRectPosition(rect);
	SIZE size = RectUtil::getRectSize(rect);
	ScreenCaptureSettings settings = _settingsManager.getSettings();
	WindowCapture* capture = NULL;
	switch (settings.method)
	{
		default:
		case ScreenCaptureMethodBitBltGetBitmapBits:
		{
			capture = new BitBltGetBitmapBitsCapture(desktop, position, size);
			break;
		}
		case ScreenCaptureMethodBitBltGetDIBits:
		{
			capture = new BitBltGetDIBitsCapture(desktop, position, size);
			break;
		}
		case ScreenCaptureMethodBitBltDIBSection:
		{
			capture = new BitBltDIBSectionCapture(desktop, position, size);
			break;
		}
		case ScreenCaptureMethodDXGIOutputDuplication:
		{
			capture = new DXGIOutputDuplicationCapture(desktop, position, size);
			break;
		}
	}
	if (settings.showCursor)
	{
		MouseOverlay* overlay = new MouseOverlay(desktop, position);
		capture->addOverlay(overlay);
	}
	capture->start(settings.frameRate);
	return capture;
}
