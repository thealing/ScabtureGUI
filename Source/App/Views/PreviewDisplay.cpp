#include "PreviewDisplay.h"

PreviewDisplay::PreviewDisplay(Window* parent) : _printTime(0), _dirty(true), _disabled(false), _highQuality(false), _width(0), _height(0), _stride(0)
{
	create(L"STATIC", NULL, 0, 0, parent);
	addCallback(subclassProc);
}

PreviewDisplay::~PreviewDisplay()
{
	removeCallback(subclassProc);
}

void PreviewDisplay::invalidate()
{
	_timer++;
	postMessage(WM_PAINT, 0, _timer);
}

void PreviewDisplay::setPaintCallback(const Callback& callback)
{
	_paintCallback = callback;
}

void PreviewDisplay::setDisabled(bool disabled)
{
	if (_disabled != disabled)
	{
		_dirty = true;
		_disabled = disabled;
	}
}

void PreviewDisplay::setHighQuality(bool highQuality)
{
	if (_highQuality != highQuality)
	{
		_dirty = true;
		_highQuality = highQuality;
	}
}

void PreviewDisplay::setUpscale(bool upscale)
{
	if (_upscale != upscale)
	{
		_dirty = true;
		_upscale = upscale;
	}
}

void PreviewDisplay::drawPreview(const Buffer* buffer)
{
	int width = buffer->getWidth();
	int height = buffer->getHeight();
	int stride = buffer->getStride();
	updateSize(width, height, stride);
	HWND handle = getHandle();
	RECT rect = {};
	GetClientRect(handle, &rect);
	if (IsRectEmpty(&rect))
	{
		return;
	}
	if (_disabled)
	{
		drawPreviewDisabled();
	}
	else
	{
		const void* pixels = buffer->beginReading();
		drawPreview(pixels);
		buffer->endReading();
	}
}

void PreviewDisplay::onResize()
{
	updateControl();
}

void PreviewDisplay::updateSize(int width, int height, int stride)
{
	if (_width == width && _height == height && _stride == stride)
	{
		return;
	}
	_width = width;
	_height = height;
	_stride = stride;
	updateControl();
}

void PreviewDisplay::updateControl()
{
	if (_width < 1 || _height < 1 || _stride < 1)
	{
		moveControl(0, 0, 0, 0);
		return;
	}
	int captureWidth = max(1, _width);
	int captureHeight = max(1, _height);
	Window* parent = getParent();
	Vector parentSize = parent->getSize();
	RECT rect = { 2, 66, parentSize.x - 2, parentSize.y - 81 };
	int displayWidth = RectUtil::getRectWidth(rect);
	int displayHeight = RectUtil::getRectHeight(rect);
	if (displayWidth < 10 || displayHeight < 10)
	{
		moveControl(0, 0, 0, 0);
		return;
	}
	if (!_upscale)
	{
		displayWidth = min(displayWidth, captureWidth);
		displayHeight = min(displayHeight, captureHeight);
	}
	displayWidth = min(displayWidth, displayHeight * captureWidth / captureHeight);
	displayHeight = min(displayHeight, displayWidth * captureHeight / captureWidth);
	int positionX = (rect.left + rect.right) / 2 - displayWidth / 2;
	int positionY = (rect.top + rect.bottom) / 2 - displayHeight / 2;
	moveControl(positionX, positionY, displayWidth, displayHeight);
	invalidate();
}

void PreviewDisplay::moveControl(int x, int y, int width, int height)
{
	_dirty = true;
	HWND handle = getHandle();
	RECT oldRect = {};
	GetWindowRect(handle, &oldRect);
	MoveWindow(handle, x, y, width, height, FALSE);
	HWND parentHandle = GetParent(handle);
	RedrawWindow(parentHandle, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ERASENOW | RDW_UPDATENOW);
}

void PreviewDisplay::drawPreview(const void* pixels)
{
	BITMAPINFO bitmapInfo = {};
	bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo);
	bitmapInfo.bmiHeader.biWidth = _stride;
	bitmapInfo.bmiHeader.biHeight = -_height;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biSizeImage = _stride * _height * 4;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	Vector displaySize = getSize();
	HDC context = getContext();
	SetStretchBltMode(context, _highQuality ? HALFTONE : COLORONCOLOR);
	StretchDIBits(context, 0, 0, displaySize.x, displaySize.y, 0, 0, _width, _height, pixels, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void PreviewDisplay::drawPreviewDisabled()
{
	if (!_dirty)
	{
		return;
	}
	_dirty = false;
	HDC context = getContext();
	Graphics graphics(context);
	FontStore& fontStore = FontStore::getInstance();
	graphics.setFont(*fontStore.getDisplayFont());
	graphics.setTextColor(255);
	graphics.setBackgroundColor(0);
	graphics.clear(0);
	graphics.drawString(L"Preview Disabled", AlignmentMiddleCenter, 0, getSize());
}

LRESULT PreviewDisplay::subclassProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR subclassId, DWORD_PTR)
{
	PreviewDisplay* instance = (PreviewDisplay*)subclassId;
	if (message == WM_PAINT)
	{
		int time = (int)lParam;
		if (time > instance->_printTime)
		{
			instance->_paintCallback.invoke();
			instance->_printTime = instance->_timer;
		}
		return DefWindowProc(window, message, wParam, lParam);
	}
	return DefSubclassProc(window, message, wParam, lParam);
}
