#pragma once

enum WindowCaptureMethod : int
{
	WindowCaptureMethodBitBltGetBitmapBits,
	WindowCaptureMethodBitBltGetDIBits,
	WindowCaptureMethodBitBltDIBSection,
	WindowCaptureMethodPrintWindowGetBitmapBits,
	WindowCaptureMethodPrintWindowGetDIBits,
	WindowCaptureMethodPrintWindowDIBSection,
	WindowCaptureMethodDwmGetDxSharedSurface,
	WindowCaptureMethodCount
};
