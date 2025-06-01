#include "Graphics.h"

Graphics::Graphics(HDC handle)
{
	_handle = handle;
}

void Graphics::setTextColor(Color color)
{
	SetTextColor(_handle, color);
}

void Graphics::setBackgroundColor(Color color)
{
	SetBkColor(_handle, color);
}

void Graphics::setBrush(const Brush& brush)
{
	SelectObject(_handle, brush._handle);
}

void Graphics::setPen(const Pen& pen)
{
	SelectObject(_handle, pen._handle);
}

void Graphics::setFont(const Font& font)
{
	SelectObject(_handle, font._handle);
}

void Graphics::drawLine(const Line& line)
{
	MoveToEx(_handle, line.start.x, line.start.y, NULL);
	LineTo(_handle, line.end.x, line.end.y);
}

void Graphics::drawRect(const Rect& rect)
{
	Rectangle(_handle, rect.lower.x, rect.lower.y, rect.upper.x, rect.upper.y);
}

void Graphics::drawString(const wchar_t* string, Alignment alignment, Vector position, Vector size)
{
	UINT format = getAlignmentFormat(alignment);
	format |= DT_NOCLIP | DT_SINGLELINE;
	RECT rect = { position.x, position.y, position.x + size.x, position.y + size.y };
	DrawText(_handle, string, (int)wcslen(string), &rect, format);
}

void Graphics::drawImage(const Image& image, Vector position)
{
	BITMAP bitmap = {};
	GetObject(image._bitmap, sizeof(BITMAP), &bitmap);
	BitBlt(_handle, position.x, position.y, bitmap.bmWidth, bitmap.bmHeight, image._context, 0, 0, SRCCOPY);
}

void Graphics::blendImage(const Image& image, Vector position, int alpha)
{
	BITMAP bitmap = {};
	GetObject(image._bitmap, sizeof(BITMAP), &bitmap);
	BLENDFUNCTION blendFunction = {};
	blendFunction.SourceConstantAlpha = (BYTE)alpha;
	AlphaBlend(_handle, position.x, position.y, bitmap.bmWidth, bitmap.bmHeight, image._context, 0, 0, bitmap.bmWidth, bitmap.bmHeight, blendFunction);
}

void Graphics::fillRect(const Rect& rect, const Brush& brush)
{
	RECT rc = { rect.lower.x, rect.lower.y, rect.upper.x, rect.upper.y };
	FillRect(_handle, &rc, brush._handle);
}

void Graphics::clear(Color color)
{
	uint32_t pixel = RGB(color.blue, color.green, color.red);
	BITMAPINFO bitmapInfo = {};
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biWidth = 1;
	bitmapInfo.bmiHeader.biHeight = -1;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	int width = GetDeviceCaps(_handle, HORZRES);
	int height = GetDeviceCaps(_handle, VERTRES);
	StretchDIBits(_handle, 0, 0, width, height, 0, 0, 1, 1, &pixel, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

HDC Graphics::getHandle() const
{
	return _handle;
}

UINT Graphics::getAlignmentFormat(Alignment alignment)
{
	switch (alignment)
	{
		case AlignmentTopLeft:
		{
			return DT_LEFT | DT_TOP;
		}
		case AlignmentTopCenter:
		{
			return DT_CENTER | DT_TOP;
		}
		case AlignmentTopRight:
		{
			return DT_RIGHT | DT_TOP;
		}
		case AlignmentMiddleLeft:
		{
			return DT_LEFT | DT_VCENTER;
		}
		case AlignmentMiddleCenter:
		{
			return DT_CENTER | DT_VCENTER;
		}
		case AlignmentMiddleRight:
		{
			return DT_RIGHT | DT_VCENTER;
		}
		case AlignmentBottomLeft:
		{
			return DT_LEFT | DT_BOTTOM;
		}
		case AlignmentBottomCenter:
		{
			return DT_CENTER | DT_BOTTOM;
		}
		case AlignmentBottomRight:
		{
			return DT_RIGHT | DT_BOTTOM;
		}
		default:
		{
			return 0;
		}
	}
}
