#include "CustomButton.h"

CustomButton::CustomButton(Window* parent, const Image* image)
{
	_image = image;
	create(L"BUTTON", NULL, WS_BORDER | BS_OWNERDRAW | BS_PUSHBUTTON, parent);
}

void CustomButton::setImage(const Image* image)
{
	_image = image;
	repaint();
}

const Event* CustomButton::getClickEvent() const
{
    return getChangeEvent();
}

void CustomButton::doCustomPaint(Graphics& graphics, bool disabled, bool selected)
{
	if (_image == NULL)
	{
		return;
	}
	if (!disabled && !selected)
	{
		graphics.drawImage(*_image, Vector(0, 0));
		return;
	}
	graphics.clear(0);
	if (disabled)
	{
		graphics.blendImage(*_image, Vector(0, 0), 100);
		return;
	}
	if (selected)
	{
		graphics.blendImage(*_image, Vector(0, 0), 200);
		return;
	}
}
