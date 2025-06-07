#pragma once

struct VideoSettings
{
	WindowArea windowArea;
	CaptureMethod captureMethod;
	bool showCursor;
	int frameRate;
	int bitRate;
	bool doResize;
	bool keepRatio;
	int width;
	int height;
	EncodeFormat encodeFormat;
	ResizeMode resizeMode;
	bool resizeQuality;
};
