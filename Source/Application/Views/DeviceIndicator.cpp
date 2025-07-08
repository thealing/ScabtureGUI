#include "DeviceIndicator.h"

DeviceIndicator::DeviceIndicator(Window* parent, const Image* image) : Picture(parent, image)
{
	_status = DeviceStatusActive;
}

void DeviceIndicator::setStatus(DeviceStatus status)
{
	if (_status != status)
	{
		_status = status;
		repaint();
	}
}

void DeviceIndicator::doCustomPaint(Graphics& graphics, bool disabled, bool selected)
{
	Picture::doCustomPaint(graphics, disabled, selected);
	switch (_status)
	{
		case DeviceStatusActive:
		{
			break;
		}
		case DeviceStatusInactive:
		{
			Color color(40, 40, 40);
			drawCrossLine(graphics, color, 2);
			break;
		}
		case DeviceStatusUnavailable:
		{
			Color color(220, 0, 0);
			drawCrossLine(graphics, color, 2);
			break;
		}
	}
}

void DeviceIndicator::drawCrossLine(Graphics& graphics, Color color, int width)
{
	Pen pen(color, width);
	graphics.setPen(pen);
	Vector size = getSize();
	Line line(size.x - width, width, width, size.y - width);
	graphics.drawLine(line);
}
