#include "Rect.h"

Rect::Rect() : lower(), upper()
{
}

Rect::Rect(Vector lower, Vector upper) : lower(lower), upper(upper)
{
}

Rect::Rect(int lowerX, int lowerY, int upperX, int upperY) : lower(lowerX, lowerY), upper(upperX, upperY)
{
}

Vector Rect::getSize() const
{
	return upper - lower;
}
