#include "WindowSelector.h"

WindowSelector::WindowSelector(WindowArea area) : _area(area), _selectedWindow(NULL)
{
}

bool WindowSelector::hasSelectedWindow() const
{
	return _selectedWindow != NULL;
}

HWND WindowSelector::getSelectedWindow() const
{
	return _selectedWindow;
}

void WindowSelector::onMouseMove(int mouseX, int mouseY)
{
	POINT mousePoint = { mouseX, mouseY };
	HWND handle = getHandle();
	_selectedWindow = WindowUtil::findWindowUnderPoint(mousePoint, handle);
	RECT rect = WindowUtil::getAbsoluteRect(_selectedWindow, _area);
	setRect(rect);
}

void WindowSelector::onMouseClick(int, int)
{
	postMessage(WM_CLOSE, 0, 0);
}

void WindowSelector::onKeyPress()
{
	_selectedWindow = NULL;
	postMessage(WM_CLOSE, 0, 0);
}
