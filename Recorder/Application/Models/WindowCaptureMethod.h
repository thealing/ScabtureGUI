#pragma once

enum WindowCaptureMethod : int
{
	WindowCaptureMethodDefault,
	WindowCaptureMethodBitBlt,
	WindowCaptureMethodPrintWindow,
	WindowCaptureMethodSharedSurface,
	WindowCaptureMethodCount
};
