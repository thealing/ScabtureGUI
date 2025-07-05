#include "MouseOverlay.h"

MouseOverlay::MouseOverlay(HWND window, POINT offset)
{
	_window = window;
	_offset = offset;
}

void MouseOverlay::draw(uint32_t* pixels, int width, int height, int stride)
{
	CURSORINFO cursorInfo = {};
	cursorInfo.cbSize = sizeof(cursorInfo);
	if (!GetCursorInfo(&cursorInfo))
	{
		return;
	}
	if (cursorInfo.flags != CURSOR_SHOWING)
	{
		return;
	}
	ICONINFO iconInfo = {};
	if (!GetIconInfo(cursorInfo.hCursor, &iconInfo))
	{
		return;
	}
	if (iconInfo.hbmColor == NULL && iconInfo.hbmMask == NULL)
	{
		return;
	}
	POINT offset = _offset;
	ClientToScreen(_window, &offset);
	int iconX = cursorInfo.ptScreenPos.x - offset.x;
	int iconY = cursorInfo.ptScreenPos.y - offset.y;
	BITMAP iconBitmap = {};
	int iconWidth = 0;
	int iconHeight = 0;
	if (iconInfo.hbmColor != NULL)
	{
		GetObject(iconInfo.hbmColor, sizeof(BITMAP), &iconBitmap);
		iconWidth = iconBitmap.bmWidth;
		iconHeight = iconBitmap.bmHeight;
	}
	else
	{
		GetObject(iconInfo.hbmMask, sizeof(BITMAP), &iconBitmap);
		iconWidth = iconBitmap.bmWidth;
		iconHeight = iconBitmap.bmHeight / 2;
	}
	BITMAPINFO bitmapInfo = {};
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = iconBitmap.bmWidth;
	bitmapInfo.bmiHeader.biHeight = -iconBitmap.bmHeight;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	uint32_t* imageBits = new uint32_t[iconWidth * iconHeight];
	uint32_t* maskBits = new uint32_t[iconWidth * iconHeight];
	HDC context = CreateCompatibleDC(NULL);
	if (iconInfo.hbmColor != NULL)
	{
		GetDIBits(context, iconInfo.hbmColor, 0, iconHeight, imageBits, &bitmapInfo, DIB_RGB_COLORS);
		GetDIBits(context, iconInfo.hbmMask, 0, iconHeight, maskBits, &bitmapInfo, DIB_RGB_COLORS);
	}
	else
	{
		GetDIBits(context, iconInfo.hbmMask, 0, iconHeight, imageBits, &bitmapInfo, DIB_RGB_COLORS);
		GetDIBits(context, iconInfo.hbmMask, iconHeight, iconHeight, maskBits, &bitmapInfo, DIB_RGB_COLORS);
	}
	DeleteDC(context);
	for (int i = 0; i < iconHeight; i++)
	{
		for (int j = 0; j < iconWidth; j++)
		{
			int x = iconX - iconInfo.xHotspot + j;
			int y = iconY - iconInfo.yHotspot + i;
			if (x < 0 || x >= width || y < 0 || y >= height)
			{
				continue;
			}
			if (iconInfo.hbmColor != NULL)
			{
				uint8_t* pixel = (uint8_t*)(imageBits + i * iconWidth + j);
				uint8_t* mask = (uint8_t*)(maskBits + i * iconWidth + j);
				uint8_t* source = (uint8_t*)(pixels + y * stride + x);
				for (int k = 0; k < 4; k++)
				{
					source[k] = (source[k] * (255 - pixel[3]) + pixel[k] * pixel[3]) / 255;
				}
			}
			else
			{
				uint32_t pixel = *(imageBits + i * iconWidth + j);
				uint32_t mask = *(maskBits + i * iconWidth + j);
				uint32_t* source = pixels + y * stride + x;
				if ((pixel ^ mask) == 0)
				{
					*source = (*source & pixel) ^ mask;
				}
			}
		}
	}
	DeleteObject(iconInfo.hbmColor);
	DeleteObject(iconInfo.hbmMask);
	delete[] imageBits;
	delete[] maskBits;
}
