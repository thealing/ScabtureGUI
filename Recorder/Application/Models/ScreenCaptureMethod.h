#pragma once

enum ScreenCaptureMethod : int
{
	ScreenCaptureMethodBitBltGetBitmapBits,
	ScreenCaptureMethodBitBltGetDIBits,
	ScreenCaptureMethodBitBltDIBSection,
	ScreenCaptureMethodDXGIOutputDuplication,
	ScreenCaptureMethodCount
};
