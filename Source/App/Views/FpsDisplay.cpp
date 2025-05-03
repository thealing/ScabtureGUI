#include "FpsDisplay.h"

FpsDisplay::FpsDisplay(Window* parent) : Frame(parent)
{
	_captureFps = 0;
	_encodeFps = 0;
	setAnchor(AnchorTopRight);
	setBounds(Rect(0, 0, 100, 65));
}

void FpsDisplay::update(int captureFps, int encodeFps)
{
	_captureFps = captureFps;
	_encodeFps = encodeFps;
	repaint();
}

void FpsDisplay::doPaint(Graphics& graphics)
{
	Frame::doPaint(graphics);
	Font font(L"Consolas", 60, 700);
	graphics.setFont(font);
	if (_captureFps <= _encodeFps)
	{
		graphics.setTextColor(Color(0, 220, 0));
	}
	else
	{
		graphics.setTextColor(Color(200, 0, 0));
	}
	wchar_t fpsText[12] = {};
	swprintf(fpsText, ARRAYSIZE(fpsText), L"%3i", min(_captureFps, _encodeFps));
	graphics.drawString(fpsText, AlignmentMiddleCenter, Vector(0, 0), getSize());
}
