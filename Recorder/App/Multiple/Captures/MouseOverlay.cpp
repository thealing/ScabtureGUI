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
	RECT rect = {};
	GetWindowRect(_window, &rect);
	int iconX = cursorInfo.ptScreenPos.x - _offset.x - rect.left;
	int iconY = cursorInfo.ptScreenPos.y - _offset.y - rect.top;
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
	bitmapInfo.bmiHeader.biSizeImage = iconBitmap.bmWidth * iconBitmap.bmHeight * 4;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	uint8_t* imageBits = new uint8_t[iconWidth * iconHeight * 4];
	uint8_t* maskBits = new uint8_t[iconWidth * iconHeight * 4];
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
			uint8_t* pixel = imageBits + (i * iconWidth + j) * 4;
			uint8_t* mask = maskBits + (i * iconWidth + j) * 4;
			uint8_t* source = (uint8_t*)(pixels + y * stride + x);
			if (iconInfo.hbmColor != NULL)
			{
				for (int k = 0; k < 4; k++)
				{
					source[k] = (source[k] * (255 - pixel[3]) + pixel[k] * pixel[3]) / 255;
				}
			}
			else if ((*(uint32_t*)pixel ^ *(uint32_t*)mask) == 0)
			{
				for (int k = 0; k < 4; k++)
				{
					source[k] = (source[k] & pixel[k]) ^ mask[k];
				}
			}
		}
	}
	DeleteObject(iconInfo.hbmColor);
	DeleteObject(iconInfo.hbmMask);
	delete[] imageBits;
	delete[] maskBits;
}
