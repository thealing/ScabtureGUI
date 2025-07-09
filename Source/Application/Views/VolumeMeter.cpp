#include "VolumeMeter.h"

VolumeMeter::VolumeMeter(Window* parent)
{
	_leftVolume = 0;
	_rightVolume = 0;
	create(L"STATIC", NULL, 0, parent);
}

VolumeMeter::~VolumeMeter()
{
}

void VolumeMeter::setVolumes(float leftVolume, float rightVolume)
{
	if (_leftVolume == leftVolume && _rightVolume == rightVolume)
	{
		return;
	}
	_leftVolume = leftVolume;
	_rightVolume = rightVolume;
	repaint();
}

void VolumeMeter::onResize()
{
	Control::onResize();
	Vector size = getSize();
	uint32_t* pixels = new uint32_t[size.x * size.y];
	for (int x = 0; x < size.x; x++)
	{
		float progress = (float)x / (float)(size.x - 1);
		float red = (1.0f - progress) * 200 + progress * 255;
		float green = (1.0f - progress) * 240 + progress * 50;
		for (int y = 0; y < size.y; y++)
		{
			pixels[x + y * size.x] = (uint32_t)red << 16 | (uint32_t)green << 8;
		}
	}
	_image = new Image(size.x, size.y, pixels);
	delete[] pixels;
}

void VolumeMeter::doPaint(Graphics& graphics)
{
	if (_image == NULL)
	{
		return;
	}
	graphics.drawImage(*_image, 0);
	int tickCount = 6;
	Pen borderPen(50, 1);
	Brush backgroundBrush(120);
	Vector size = getSize();
	int gapTop = size.y * 2 / 5;
	int gapBottom = size.y - size.y * 2 / 5;
	int leftX = (int)((float)size.x * _leftVolume);
	int rightX = (int)((float)size.x * _rightVolume);
	Rect emptyRect(0, gapTop, size.x, gapBottom);
	Brush whiteBrush(255);
	graphics.fillRect(emptyRect, whiteBrush);
	Brush hollowBrush;
	graphics.setBrush(hollowBrush);
	graphics.setPen(borderPen);
	Rect topRect(0, 0, size.x, gapTop);
	topRect.lower.x = leftX;
	graphics.fillRect(topRect, backgroundBrush);
	topRect.lower.x = 0;
	graphics.drawRect(topRect);
	Rect bottomRect(0, gapBottom, size.x, size.y);
	bottomRect.lower.x = rightX;
	graphics.fillRect(bottomRect, backgroundBrush);
	bottomRect.lower.x = 0;
	graphics.drawRect(bottomRect);
	for (int i = 1; i < tickCount; i++)
	{
		int x = size.x * i / tickCount;
		if (x >= leftX)
		{
			Line line(x, 0, x, gapTop);
			graphics.drawLine(line);
		}
		if (x >= rightX)
		{
			Line line(x, gapBottom, x, size.y);
			graphics.drawLine(line);
		}
	}
}
