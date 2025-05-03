#include "Brush.h"

Brush::Brush()
{
	LOGBRUSH brushDefinition = {};
	brushDefinition.lbStyle = BS_HOLLOW;
	_handle = CreateBrushIndirect(&brushDefinition);
}

Brush::Brush(Color color)
{
	COLORREF rgbValue = RGB(color.red, color.green, color.blue);
	_handle = CreateSolidBrush(rgbValue);
}

Brush::~Brush()
{
	DeleteObject(_handle);
}
