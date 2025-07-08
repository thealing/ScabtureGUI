#include "MouseOverlay.h"

MouseOverlay::MouseOverlay(HWND window, POINT offset)
{
	_window = window;
	_offset = offset;
	_screenContext = CreateCompatibleDC(NULL);
}

MouseOverlay::~MouseOverlay()
{
	DeleteDC(_screenContext);
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
	uint32_t* imageBits = BufferUtil::allocateBuffer<uint32_t>(iconWidth * iconHeight);
	uint32_t* maskBits = BufferUtil::allocateBuffer<uint32_t>(iconWidth * iconHeight);
	if (iconInfo.hbmColor != NULL)
	{
		GetDIBits(_screenContext, iconInfo.hbmColor, 0, iconHeight, imageBits, &bitmapInfo, DIB_RGB_COLORS);
		GetDIBits(_screenContext, iconInfo.hbmMask, 0, iconHeight, maskBits, &bitmapInfo, DIB_RGB_COLORS);
	}
	else
	{
		GetDIBits(_screenContext, iconInfo.hbmMask, 0, iconHeight, imageBits, &bitmapInfo, DIB_RGB_COLORS);
		GetDIBits(_screenContext, iconInfo.hbmMask, iconHeight, iconHeight, maskBits, &bitmapInfo, DIB_RGB_COLORS);
	}
	for (int y = 0; y < iconHeight; y++)
	{
		for (int x = 0; x < iconWidth; x++)
		{
			int destX = iconX - iconInfo.xHotspot + x;
			int destY = iconY - iconInfo.yHotspot + y;
			if (destX < 0 || destX >= width || destY < 0 || destY >= height)
			{
				continue;
			}
			if (iconInfo.hbmColor != NULL)
			{
				uint8_t* pixel = (uint8_t*)(imageBits + y * iconWidth + x);
				uint8_t* mask = (uint8_t*)(maskBits + y * iconWidth + x);
				uint8_t* dest = (uint8_t*)(pixels + destY * stride + destX);
				int alpha = pixel[3];
				for (int i = 0; i < 3; i++)
				{
					dest[i] = (dest[i] * (255 - alpha) + pixel[i] * alpha) / 255;
				}
			}
			else
			{
				uint32_t pixel = *(imageBits + y * iconWidth + x);
				uint32_t mask = *(maskBits + y * iconWidth + x);
				uint32_t* dest = pixels + destY * stride + destX;
				if ((pixel ^ mask) == 0)
				{
					*dest = (*dest & pixel) ^ mask;
				}
			}
		}
	}
	DeleteObject(iconInfo.hbmColor);
	DeleteObject(iconInfo.hbmMask);
	BufferUtil::freeBuffer(imageBits);
	BufferUtil::freeBuffer(maskBits);
}
