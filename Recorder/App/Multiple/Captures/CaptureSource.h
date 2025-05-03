#pragma once

struct CaptureSource
{
	HWND window;
	RECT rect;
	bool client;
	int width;
	int height;
	int stride;
};

