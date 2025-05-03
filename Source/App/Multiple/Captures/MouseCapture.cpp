#include "MouseCapture.h"

MouseCapture::MouseCapture(const CaptureSource& source, Capture* capture, bool draw) : _capture(capture), _draw(draw)
{
	_offset.x = source.rect.left;
	_offset.y = source.rect.top;
	if (source.client)
	{
		ClientToScreen(source.window, &_offset);
	}
	else
	{
		RECT rect = {};
		GetWindowRect(source.window, &rect);
		_offset.x += rect.left;
		_offset.y += rect.top;
	}
	_iconInfo = {};
	_context = CreateCompatibleDC(NULL);
}

MouseCapture::~MouseCapture()
{
	DeleteObject(_iconInfo.hbmColor);
	DeleteObject(_iconInfo.hbmMask);
	DeleteDC(_context);
}

bool MouseCapture::getFrame(Buffer* buffer)
{
	bool result = _capture->getFrame(buffer);
	if (result)
	{
		drawCursor(buffer);
	}
	return result;
}

void MouseCapture::drawCursor(Buffer* buffer)
{
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
	cursorInfo.ptScreenPos.x -= _offset.x;
	cursorInfo.ptScreenPos.y -= _offset.y;
	BITMAP iconBitmap = {};
	int width;
	int height;
	if (_iconInfo.hbmColor != NULL)
	{
		GetObject(_iconInfo.hbmColor, sizeof(BITMAP), &iconBitmap);
		width = iconBitmap.bmWidth;
		height = iconBitmap.bmHeight;
	}
	else
	{
		GetObject(_iconInfo.hbmMask, sizeof(BITMAP), &iconBitmap);
		width = iconBitmap.bmWidth;
		height = iconBitmap.bmHeight / 2;
	}
	BITMAPINFO bitmapInfo = {};
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = iconBitmap.bmWidth;
	bitmapInfo.bmiHeader.biHeight = -iconBitmap.bmHeight;
	bitmapInfo.bmiHeader.biSizeImage = iconBitmap.bmWidth * iconBitmap.bmHeight * 4;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	uint8_t* imageBits = new uint8_t[width * height * 4];
	uint8_t* maskBits = new uint8_t[width * height * 4];
	if (_iconInfo.hbmColor != NULL)
	{
		GetDIBits(_context, _iconInfo.hbmColor, 0, height, imageBits, &bitmapInfo, DIB_RGB_COLORS);
		GetDIBits(_context, _iconInfo.hbmMask, 0, height, maskBits, &bitmapInfo, DIB_RGB_COLORS);
	}
	else
	{
		GetDIBits(_context, _iconInfo.hbmMask, 0, height, imageBits, &bitmapInfo, DIB_RGB_COLORS);
		GetDIBits(_context, _iconInfo.hbmMask, height, height, maskBits, &bitmapInfo, DIB_RGB_COLORS);
	}
	uint32_t* pixels = buffer->beginWriting();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			uint8_t* pixel = imageBits + (i * width + j) * 4;
			uint8_t* mask = maskBits + (i * width + j) * 4;
			if (*(uint32_t*)pixel == 0)
			{
				continue;
			}
			int x = cursorInfo.ptScreenPos.x - _iconInfo.xHotspot + j;
			int y = cursorInfo.ptScreenPos.y - _iconInfo.yHotspot + i;
			if (x < 0 || x >= buffer->getWidth() || y < 0 || y >= buffer->getHeight())
			{
				continue;
			}
			uint8_t* dest = (uint8_t*)(pixels + y * buffer->getStride() + x);
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
	buffer->endWriting();
	delete[] imageBits;
	delete[] maskBits;
}
