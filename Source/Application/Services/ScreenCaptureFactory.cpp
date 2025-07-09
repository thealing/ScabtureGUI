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

VideoCapture* ScreenCaptureFactory::createCapture(HWND desktopWindow, RECT rect) const
{
	POINT position = RectUtil::getRectPosition(rect);
	SIZE size = RectUtil::getRectSize(rect);
	ScreenCaptureSettings settings = _settingsManager.getSettings();
	WindowCapture* capture = NULL;
	switch (settings.method)
	{
		case ScreenCaptureMethodBitBlt:
		{
			capture = new BitBltCapture(desktopWindow, position, size);
			break;
		}
		case ScreenCaptureMethodDesktopDuplication:
		{
			capture = new DXGIOutputDuplicationCapture(desktopWindow, position, size);
			break;
		}
	}
	if (settings.showCursor)
	{
		MouseOverlay* overlay = new MouseOverlay(desktopWindow, position);
		capture->addOverlay(overlay);
	}
	capture->start(settings.frameRate);
	return capture;
}
