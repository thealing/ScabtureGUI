#include "Frame.h"

Frame::Frame(Window* parent)
{
	_borderPen = new Pen(0, 2);
	create(L"STATIC", NULL, 0, 0, parent);
}

void Frame::doPaint(Graphics& graphics)
{
	Vector size = getSize();
	Rect rect(1, 1, size.x, size.y);
	graphics.setPen(*_borderPen);
	graphics.drawRect(rect);
}
