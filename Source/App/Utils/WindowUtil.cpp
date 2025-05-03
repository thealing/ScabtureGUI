#include "WindowUtil.h"

HWND WindowUtil::getDesktopWindow()
{
    return GetDesktopWindow();
}

POINT WindowUtil::getWindowPosition(HWND window)
{
	RECT rect = {};
	GetWindowRect(window, &rect);
	POINT point = { rect.left, rect.top };
	return point;
}

HWND WindowUtil::findWindowUnderPoint(POINT point, HWND windowToSkip)
{
	HWND result = NULL;
	RECT rect = {};
	HWND window = GetDesktopWindow();
	while (window != NULL)
	{
		if (window == windowToSkip)
		{
			goto Next;
		}
		if (!IsWindowVisible(window))
		{
			goto Next;
		}
		GetWindowRect(window, &rect);
		if (PtInRect(&rect, point))
		{
			result = window;
			window = GetWindow(window, GW_CHILD);
			continue;
		}
	Next:
		window = GetWindow(window, GW_HWNDNEXT);
	}
	return result;
}

RECT WindowUtil::getAbsoluteRect(HWND window, WindowArea area)
{
	RECT rect = {};
	switch (area)
	{
		case WindowAreaDefault:
		{
			GetWindowRect(window, &rect);
			break;
		}
		case WindowAreaVisible:
		{
			HRESULT result = DwmGetWindowAttribute(window, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(RECT));
			if (FAILED(result))
			{
				GetWindowRect(window, &rect);
			}
			break;
		}
		case WindowAreaClient:
		{
			GetClientRect(window, &rect);
			POINT origin = { 0, 0 };
			ClientToScreen(window, &origin);
			OffsetRect(&rect, origin.x, origin.y);
			break;
		}
	}
	return rect;
}

RECT WindowUtil::getRelativeRect(HWND window, WindowArea area)
{
	RECT rect = {};
	switch (area)
	{
		case WindowAreaDefault:
		{
			GetWindowRect(window, &rect);
			OffsetRect(&rect, -rect.left, -rect.top);
			break;
		}
		case WindowAreaVisible:
		{
			HRESULT result = DwmGetWindowAttribute(window, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(RECT));
			if (SUCCEEDED(result))
			{
				POINT position = getWindowPosition(window);
				OffsetRect(&rect, -position.x, -position.y);
			}
			else
			{
				GetWindowRect(window, &rect);
				OffsetRect(&rect, -rect.left, -rect.top);
			}
			break;
		}
		case WindowAreaClient:
		{
			GetClientRect(window, &rect);
			break;
		}
	}
	return rect;
}
