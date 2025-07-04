#pragma once

struct VideoSettings
{
	CaptureMethod captureMethod;
	bool showCursor;
	int frameRate;
	int bitRate;
	bool resize;
	bool keepRatio;
	int width;
	int height;
	EncodeFormat encodeFormat;
	ResizeMode resizeMode;
	bool resizeQuality;
};
