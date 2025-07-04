#pragma once

struct VideoResizerSettings
{
	bool resize;
	bool keepRatio;
	int width;
	int height;
	ResizeMode mode;
	bool quality;
};
