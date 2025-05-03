#include "Pen.h"

Pen::Pen(Color color, int width)
{
	_handle = CreatePen(PS_SOLID, width, color);
}

Pen::~Pen()
{
	DeleteObject(_handle);
}
