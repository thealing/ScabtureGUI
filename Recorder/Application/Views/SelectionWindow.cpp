#include "SelectionWindow.h"

SelectionWindow::SelectionWindow() : OverlayWindow(L"Selection Window")
{
	_rect = {};
	_clicked = false;
	setAlpha(100);
	postMessage(WM_PAINT, 0, 0);
}

void SelectionWindow::setRect(const RECT& rect)
{
	_rect = rect;
	postMessage(WM_PAINT, 0, 0);
}

void SelectionWindow::onPaint()
{
	HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH whiteBrush = CreateSolidBrush(RGB(0, 255, 255));
	HDC context = getContext();
	RECT rect = { 0, 0, getWidth(), getHeight() };
	FillRect(context, &rect, blackBrush);
	FillRect(context, &_rect, whiteBrush);
	display();
}

bool SelectionWindow::handleMessage(UINT message, WPARAM, LPARAM lParam)
{
	switch (message)
	{
		case WM_KEYDOWN:
		{
			onKeyPress();
			return true;
		}
		case WM_MOUSEMOVE:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			onMouseMove(x, y);
			return true;
		}
		case WM_LBUTTONDOWN:
		{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			onMouseClick(x, y);
			return true;
		}
		case WM_PAINT:
		{
			onPaint();
			return true;
		}
		default:
		{
			return false;
		}
	}
}
