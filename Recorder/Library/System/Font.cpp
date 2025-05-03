#include "Font.h"

Font::Font(const wchar_t* name, int size, int weight)
{
	_handle = CreateFont(size, 0, 0, 0, weight, 0, 0, 0, 0, 0, 0, 0, 0, name);
}

Font::~Font()
{
	DeleteObject(_handle);
}
