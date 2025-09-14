#include "WindowComposition.h"

typedef BOOL (WINAPI* GetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
typedef BOOL (WINAPI* SetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);

BOOL getWindowCompositionAttribute(HWND window, WINDOWCOMPOSITIONATTRIBDATA* data)
{
	static DynamicLibrary user32("user32.dll");
	static GetWindowCompositionAttribute function = (GetWindowCompositionAttribute)user32.getFunction("GetWindowCompositionAttribute");
	return function != NULL && function(window, data);
}

BOOL setWindowCompositionAttribute(HWND window, WINDOWCOMPOSITIONATTRIBDATA* data)
{
	static DynamicLibrary user32("user32.dll");
	static SetWindowCompositionAttribute function = (SetWindowCompositionAttribute)user32.getFunction("SetWindowCompositionAttribute");
	return function != NULL && function(window, data);
}
