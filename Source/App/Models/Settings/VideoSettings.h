#pragma once

struct VideoSettings
{
	WindowCaptureMethod windowCaptureMethod;
	ScreenCaptureMethod screenCaptureMethod;
	bool showCursor;
	int frameRate;
	int bitRate;
	bool resize;
	bool keepRatio;
	int width;
	int height;
	EncodeFormat encodeFormat;
	ResizeMode resizeMode;
	ResizeQuality resizeQuality;
};
