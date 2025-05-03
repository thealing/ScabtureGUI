#include "Picture.h"

Picture::Picture(Window* parent, const Image* image)
{
	_image = image;
	create(L"STATIC", NULL, SS_OWNERDRAW, parent);
}

void Picture::setImage(const Image* image)
{
	_image = image;
	repaint();
}

void Picture::doCustomPaint(Graphics& graphics, bool, bool)
{
	if (_image == NULL)
	{
		return;
	}
	graphics.drawImage(*_image, Vector(0, 0));
}
