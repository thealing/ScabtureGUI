#include "VideoSettingsDialog.h"

VideoSettingsDialog::VideoSettingsDialog()
{
}

VideoSettingsDialog::~VideoSettingsDialog()
{
}

DialogWindow* VideoSettingsDialog::createWindow(Window* parent)
{
	return new DialogWindow(parent, L"Video Options", 360, 28, 10, 5);
}

void VideoSettingsDialog::createControls(DialogWindow* window, VideoSettings* settings)
{
	const wchar_t* windowCaptureMethodNames[WindowCaptureMethodCount] = {};
	windowCaptureMethodNames[WindowCaptureMethodBitBlt] = L"BitBlt";
	windowCaptureMethodNames[WindowCaptureMethodPrintWindow] = L"PrintWindow";
	windowCaptureMethodNames[WindowCaptureMethodSharedSurface] = L"Shared Surface";
	window->addComboBox(L"Window capture method", 150, (int*)&settings->windowCaptureMethod, windowCaptureMethodNames, ARRAYSIZE(windowCaptureMethodNames));
	const wchar_t* screenCaptureMethodNames[ScreenCaptureMethodCount] = {};
	screenCaptureMethodNames[ScreenCaptureMethodBitBlt] = L"BitBlt";
	screenCaptureMethodNames[ScreenCaptureMethodDesktopDuplication] = L"Desktop Duplication";
	window->addComboBox(L"Screen capture method", 150, (int*)&settings->screenCaptureMethod, screenCaptureMethodNames, ARRAYSIZE(screenCaptureMethodNames));
	window->addCheckBox(L"Exclude application window", 16, &settings->exclude);
	window->addSeparator();
	window->addCheckBox(L"Show mouse cursor", 16, &settings->showCursor);
	window->addSeparator();
	const wchar_t* resizeModeNames[ResizeModeCount] = {};
	resizeModeNames[ResizeModeStretch] = L"Stretch";
	resizeModeNames[ResizeModeLetterbox] = L"Letterbox";
	resizeModeNames[ResizeModeCrop] = L"Crop";
	window->addComboBox(L"Resize mode", 130, (int*)&settings->resizeMode, resizeModeNames, ARRAYSIZE(resizeModeNames));
	const wchar_t* resizeQualityNames[ResizeQualityCount] = {};
	resizeQualityNames[ResizeQualityNearest] = L"Nearest";
	resizeQualityNames[ResizeQualityBilinear] = L"Bilinear";
	window->addComboBox(L"Resize quality", 130, (int*)&settings->resizeQuality, resizeQualityNames, ARRAYSIZE(resizeQualityNames));
	window->addSeparator();
	const wchar_t* encodeFormatNames[EncodeFormatCount] = {};
	encodeFormatNames[EncodeFormatIYUV] = L"IYUV";
	encodeFormatNames[EncodeFormatNV12] = L"NV12";
	window->addComboBox(L"Encode format", 100, (int*)&settings->encodeFormat, encodeFormatNames, ARRAYSIZE(encodeFormatNames));
}
