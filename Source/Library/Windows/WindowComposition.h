#pragma once

enum WINDOWCOMPOSITIONATTRIB
{
	WCA_EXCLUDED_FROM_DDA = 24
};

struct WINDOWCOMPOSITIONATTRIBDATA
{
	WINDOWCOMPOSITIONATTRIB Attrib;
	void* pvData;
	UINT cbData;
};

class WindowComposition
{
public:

	static BOOL getAttribute(HWND window, WINDOWCOMPOSITIONATTRIBDATA* data);

	static BOOL setAttribute(HWND window, WINDOWCOMPOSITIONATTRIBDATA* data);

private:

	typedef BOOL WINAPI GetWindowCompositionAttribute(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
	typedef BOOL WINAPI SetWindowCompositionAttribute(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
};
