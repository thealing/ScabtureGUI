#include "MouseOverlay.h"

MouseOverlay::MouseOverlay(const CaptureSource& source, bool draw) : _draw(draw)
{
	_window = source.window;
	_client = source.client;
	_iconInfo = {};
	_context = CreateCompatibleDC(NULL);
}

MouseOverlay::~MouseOverlay()
{
	DeleteObject(_iconInfo.hbmColor);
	DeleteObject(_iconInfo.hbmMask);
	DeleteDC(_context);
}

void MouseOverlay::draw(uint32_t* pixels, int width, int height, int stride)
{
	// TODO: Clean this function
	CURSORINFO cursorInfo = {};
	cursorInfo.cbSize = sizeof(cursorInfo);
	if (!GetCursorInfo(&cursorInfo))
	{
		return;
	}
	if (cursorInfo.flags != CURSOR_SHOWING && !_draw)
	{
		return;
	}
	ICONINFO iconInfo = {};
	if (GetIconInfo(cursorInfo.hCursor, &iconInfo))
	{
		DeleteObject(_iconInfo.hbmColor);
		DeleteObject(_iconInfo.hbmMask);
		_iconInfo = iconInfo;
	}
	if (_iconInfo.hbmColor == NULL && _iconInfo.hbmMask == NULL)
	{
		return;
	}
	POINT offset = {};
	if (_client)
	{
		ClientToScreen(_window, &offset);
	}
	else
	{
		RECT rect = {};
		GetWindowRect(_window, &rect);
		offset.x += rect.left;
		offset.y += rect.top;
	}
	cursorInfo.ptScreenPos.x -= offset.x;
	cursorInfo.ptScreenPos.y -= offset.y;
	BITMAP iconBitmap = {};
	int iconWidth = 0;
	int iconHeight = 0;
	if (_iconInfo.hbmColor != NULL)
	{
		GetObject(_iconInfo.hbmColor, sizeof(BITMAP), &iconBitmap);
		iconWidth = iconBitmap.bmWidth;
		iconHeight = iconBitmap.bmHeight;
	}
	else
	{
		GetObject(_iconInfo.hbmMask, sizeof(BITMAP), &iconBitmap);
		iconWidth = iconBitmap.bmWidth;
		iconHeight = iconBitmap.bmHeight / 2;
	}
	BITMAPINFO bitmapInfo = {};
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = iconBitmap.bmWidth;
	bitmapInfo.bmiHeader.biHeight = -iconBitmap.bmHeight;
	bitmapInfo.bmiHeader.biSizeImage = iconBitmap.bmWidth * iconBitmap.bmHeight * 4;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	uint8_t* imageBits = new uint8_t[iconWidth * iconHeight * 4];
	uint8_t* maskBits = new uint8_t[iconWidth * iconHeight * 4];
	if (_iconInfo.hbmColor != NULL)
	{
		GetDIBits(_context, _iconInfo.hbmColor, 0, iconHeight, imageBits, &bitmapInfo, DIB_RGB_COLORS);
		GetDIBits(_context, _iconInfo.hbmMask, 0, iconHeight, maskBits, &bitmapInfo, DIB_RGB_COLORS);
	}
	else
	{
		GetDIBits(_context, _iconInfo.hbmMask, 0, iconHeight, imageBits, &bitmapInfo, DIB_RGB_COLORS);
		GetDIBits(_context, _iconInfo.hbmMask, iconHeight, iconHeight, maskBits, &bitmapInfo, DIB_RGB_COLORS);
	}
	for (int i = 0; i < iconHeight; i++)
	{
		for (int j = 0; j < iconWidth; j++)
		{
			uint8_t* pixel = imageBits + (i * iconWidth + j) * 4;
			uint8_t* mask = maskBits + (i * iconWidth + j) * 4;
			if (*(uint32_t*)pixel == 0)
			{
				continue;
			}
			int x = cursorInfo.ptScreenPos.x - _iconInfo.xHotspot + j;
			int y = cursorInfo.ptScreenPos.y - _iconInfo.yHotspot + i;
			if (x < 0 || x >= width || y < 0 || y >= height)
			{
				continue;
			}
			uint8_t* dest = (uint8_t*)(pixels + y * stride + x);
			if (_iconInfo.hbmColor != NULL)
			{
				for (int k = 0; k < 4; k++)
				{
					dest[k] = (dest[k] * (255 - pixel[3]) + pixel[k] * pixel[3]) / 255;
				}
			}
			else
			{
				for (int k = 0; k < 4; k++)
				{
					dest[k] ^= mask[k];
				}
			}
		}
	}
	delete[] imageBits;
	delete[] maskBits;
}
