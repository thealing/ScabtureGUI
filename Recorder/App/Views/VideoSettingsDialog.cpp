#include "VideoSettingsDialog.h"

VideoSettingsDialog::VideoSettingsDialog()
{
}

VideoSettingsDialog::~VideoSettingsDialog()
{
}

DialogWindow* VideoSettingsDialog::createWindow(Window* parent)
{
	return new DialogWindow(parent, L"Video Options", 340, 28, 10, 5);
}

void VideoSettingsDialog::createControls(DialogWindow* window, VideoSettings* settings)
{
	const wchar_t* methodNames[CaptureMethodCount] = {};
	methodNames[CaptureMethodDefault] = L"Default";
	methodNames[CaptureMethodBitBltGetDIBits] = L"BitBlt + GetDIBits";
	window->addComboBox(L"Capture method", 170, (int*)&settings->captureMethod, methodNames, ARRAYSIZE(methodNames));
	window->addSeparator();
	window->addCheckBox(L"Show mouse cursor", 16, &settings->showCursor);
	window->addSeparator();
	const wchar_t* resizeModeNames[ResizeModeCount] = {};
	resizeModeNames[ResizeModeStretch] = L"Stretch";
	resizeModeNames[ResizeModeLetterbox] = L"Letterbox";
	resizeModeNames[ResizeModeCrop] = L"Crop";
	window->addComboBox(L"Resize mode", 130, (int*)&settings->resizeMode, resizeModeNames, ARRAYSIZE(resizeModeNames));
	window->addCheckBox(L"High quality resize", 16, &settings->resizeQuality);
	window->addSeparator();
	const wchar_t* encodeFormatNames[EncodeFormatCount] = {};
	encodeFormatNames[EncodeFormatIYUV] = L"IYUV";
	encodeFormatNames[EncodeFormatNV12] = L"NV12";
	window->addComboBox(L"Encode format", 130, (int*)&settings->encodeFormat, encodeFormatNames, ARRAYSIZE(encodeFormatNames));
}
