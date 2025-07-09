#include "RectangleSelector.h"

RectangleSelector::RectangleSelector()
{
	_clicked = false;
	_startX = 0;
	_startY = 0;
	_selectedRect = {};
}

bool RectangleSelector::hasSelectedRect() const
{
	return _selectedRect.left < _selectedRect.right && _selectedRect.top < _selectedRect.bottom;
}

RECT RectangleSelector::getSelectedRect() const
{
	return _selectedRect;
}

void RectangleSelector::onMouseMove(int mouseX, int mouseY)
{
	if (_clicked)
	{
		_selectedRect.left = min(_startX, mouseX);
		_selectedRect.top = min(_startY, mouseY);
		_selectedRect.right = max(_startX, mouseX);
		_selectedRect.bottom = max(_startY, mouseY);
		setRect(_selectedRect);
	}
}

void RectangleSelector::onMouseClick(int mouseX, int mouseY)
{
	if (_clicked)
	{
		postMessage(WM_CLOSE, 0, 0);
	}
	else
	{
		_clicked = true;
		_startX = mouseX;
		_startY = mouseY;
	}
}

void RectangleSelector::onKeyPress()
{
	SetRectEmpty(&_selectedRect);
	postMessage(WM_CLOSE, 0, 0);
}
