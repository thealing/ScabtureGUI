#include "Line.h"

Line::Line() : start(0), end(0)
{
}

Line::Line(Vector start, Vector end) : start(start), end(end)
{
}

Line::Line(int startX, int startY, int endX, int endY) : start(startX, startY), end(endX, endY)
{
}
