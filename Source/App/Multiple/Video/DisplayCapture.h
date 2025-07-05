#pragma once

class DisplayCapture : public ScreenCapture
{
public:

	DisplayCapture(RECT rect, int frameRate, bool showCursor);
};

