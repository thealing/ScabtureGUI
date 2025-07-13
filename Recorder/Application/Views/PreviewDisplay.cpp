#include "PreviewDisplay.h"

PreviewDisplay::PreviewDisplay(Window* parent)
{
	_dirty = true;
	_disabled = false;
	_highQuality = false;
	_upscale = false;
	_width = 0;
	_height = 0;
	_stride = 0;
	_pixels = NULL;
	create(L"STATIC", NULL, 0, 0, parent);
}

PreviewDisplay::~PreviewDisplay()
{
	if (_pixels != NULL)
	{
		BufferUtil::freeBuffer(_pixels);
	}
}

void PreviewDisplay::draw()
{
	WriteLockHolder holder(&_lock);
	if (_disabled)
	{
		if (_dirty)
		{
			_dirty = false;
			invalidate();
		}
	}
	else
	{
		invalidate();
	}
}

void PreviewDisplay::setDisabled(bool disabled)
{
	WriteLockHolder holder(&_lock);
	if (_disabled != disabled)
	{
		_disabled = disabled;
		_dirty = true;
		invalidate();
	}
}

void PreviewDisplay::setHighQuality(bool highQuality)
{
	WriteLockHolder holder(&_lock);
	if (_highQuality != highQuality)
	{
		_highQuality = highQuality;
		_dirty = true;
		invalidate();
	}
}

void PreviewDisplay::setUpscale(bool upscale)
{
	WriteLockHolder holder(&_lock);
	if (_upscale != upscale)
	{
		_upscale = upscale;
		_dirty = true;
		postTask(BIND(PreviewDisplay, updateControl, this));
	}
}

void PreviewDisplay::setBuffer(const Buffer* buffer)
{
	if (buffer != NULL)
	{
		int width = buffer->getWidth();
		int height = buffer->getHeight();
		int stride = buffer->getStride();
		_lock.beginReading();
		if (_pixels != NULL && _width == width && _height == height && _stride == stride)
		{
			Vector size = getSize();
			if (size.x > 0 && size.y > 0)
			{
				const uint32_t* source = buffer->beginReading();
				BufferUtil::copyBuffer(_pixels, source, _stride * _height);
				buffer->endReading();
			}
			_lock.endReading();
		}
		else
		{
			_lock.endReading();
			_lock.beginWriting();
			if (_pixels != NULL)
			{
				BufferUtil::freeBuffer(_pixels);
			}
			_width = width;
			_height = height;
			_stride = stride;
			_pixels = BufferUtil::allocateBuffer<uint32_t>(_stride * _height);
			_dirty = true;
			_lock.endWriting();
			updateControl();
		}
	}
	else
	{
		WriteLockHolder holder(&_lock);
		if (_pixels != NULL)
		{
			BufferUtil::freeBuffer(_pixels);
		}
		_width = 0;
		_height = 0;
		_stride = 0;
		_pixels = NULL;
	}
}

void PreviewDisplay::updateControl()
{
	_lock.beginReading();
	int width = _width;
	int height = _height;
	bool upscale = _upscale;
	_lock.endReading();
	if (width < 1 || height < 1)
	{
		moveControl(0, 0, 0, 0);
		return;
	}
	int captureWidth = max(1, width);
	int captureHeight = max(1, height);
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
	if (!upscale)
	{
		displayWidth = min(displayWidth, captureWidth);
		displayHeight = min(displayHeight, captureHeight);
	}
	displayWidth = min(displayWidth, displayHeight * captureWidth / captureHeight);
	displayHeight = min(displayHeight, displayWidth * captureHeight / captureWidth);
	int positionX = (rect.left + rect.right) / 2 - displayWidth / 2;
	int positionY = (rect.top + rect.bottom) / 2 - displayHeight / 2;
	moveControl(positionX, positionY, displayWidth, displayHeight);
}

void PreviewDisplay::moveControl(int x, int y, int width, int height)
{
	HWND handle = getHandle();
	SetWindowPos(handle, NULL, x, y, width, height, SWP_NOZORDER | SWP_ASYNCWINDOWPOS);
}

void PreviewDisplay::drawPreview(Graphics& graphics)
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
	HDC context = graphics.getHandle();
	SetStretchBltMode(context, _highQuality ? HALFTONE : COLORONCOLOR);
	StretchDIBits(context, 0, 0, displaySize.x, displaySize.y, 0, 0, _width, _height, _pixels, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	leaveBlock();
}

void PreviewDisplay::drawPreviewDisabled(Graphics& graphics)
{
	FontStore& fontStore = FontStore::getInstance();
	graphics.setFont(*fontStore.getDisplayFont());
	graphics.setTextColor(255);
	graphics.setBackgroundColor(0);
	graphics.clear(0);
	graphics.drawString(L"Preview Disabled", AlignmentMiddleCenter, 0, getSize());
}

void PreviewDisplay::drawPreviewInactive(Graphics& graphics)
{
	graphics.clear(0);
}

void PreviewDisplay::onResize()
{
	updateControl();
}

void PreviewDisplay::doPaint(Graphics& graphics)
{
	ReadLockHolder holder(&_lock);
	Vector size = getSize();
	if (size.x == 0 || size.y == 0)
	{
		return;
	}
	if (_pixels == NULL)
	{
		drawPreviewInactive(graphics);
	}
	else if (_disabled)
	{
		drawPreviewDisabled(graphics);
	}
	else
	{
		drawPreview(graphics);
	}
}
