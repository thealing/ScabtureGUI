#include "WindowUtil.h"

POINT WindowUtil::getWindowPosition(HWND window)
{
	RECT rect = {};
	GetWindowRect(window, &rect);
	POINT point = { rect.left, rect.top };
	return point;
}

SIZE WindowUtil::getClientSize(HWND window)
{
	RECT rect = {};
	GetClientRect(window, &rect);
	int width = RectUtil::getRectWidth(rect);
	int height = RectUtil::getRectHeight(rect);
	SIZE size = { width, height };
	return size;
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
	HWND rootWindow = GetAncestor(window, GA_ROOT);
	POINT rootPosition = getWindowPosition(rootWindow);
	origin.x -= rootPosition.x;
	origin.y -= rootPosition.y;
	OffsetRect(&clientRect, origin.x, origin.y);
	return clientRect;
}
