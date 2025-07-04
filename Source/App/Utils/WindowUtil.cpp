#include "WindowUtil.h"

POINT WindowUtil::getWindowPosition(HWND window)
{
	RECT rect = {};
	GetWindowRect(window, &rect);
	POINT point = { rect.left, rect.top };
	return point;
}

RECT WindowUtil::getAbsoluteClientRect(HWND window)
{
	RECT clientRect = {};
	GetClientRect(window, &clientRect);
	POINT origin = {};
	ClientToScreen(window, &origin);
	OffsetRect(&clientRect, origin.x, origin.y);
	return clientRect;
}

RECT WindowUtil::getRelativeClientRect(HWND window)
{
	RECT clientRect = {};
	GetClientRect(window, &clientRect);
	POINT origin = {};
	ClientToScreen(window, &origin);
	POINT position = getWindowPosition(window);
	origin.x -= position.x;
	origin.y -= position.y;
	OffsetRect(&clientRect, origin.x, origin.y);
	return clientRect;
}
