#include "WindowComposition.h"

BOOL WindowComposition::getAttribute(HWND window, WINDOWCOMPOSITIONATTRIBDATA* data)
{
	static DynamicLibrary user32("user32.dll");
	static GetWindowCompositionAttribute* function = user32.getFunction<GetWindowCompositionAttribute>("GetWindowCompositionAttribute");
	return function != NULL && function(window, data);
}

BOOL WindowComposition::setAttribute(HWND window, WINDOWCOMPOSITIONATTRIBDATA* data)
{
	static DynamicLibrary user32("user32.dll");
	static SetWindowCompositionAttribute* function = user32.getFunction<SetWindowCompositionAttribute>("SetWindowCompositionAttribute");
	return function != NULL && function(window, data);
}
