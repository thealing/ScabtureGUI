#include "Image.h"

Image::Image(int width, int height, void* pixels)
{
	_bitmap = CreateBitmap(width, height, 1, 32, pixels);
	_context = CreateCompatibleDC(NULL);
	SelectObject(_context, _bitmap);
}

Image::Image(int resourceId)
{
	HINSTANCE module = GetModuleHandle(NULL);
	_bitmap = (HBITMAP)LoadImage(module, MAKEINTRESOURCE(resourceId), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
	_context = CreateCompatibleDC(NULL);
	SelectObject(_context, _bitmap);
}

Image::~Image()
{
	DeleteDC(_context);
	DeleteObject(_bitmap);
}
