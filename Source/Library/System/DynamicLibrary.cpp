#include "DynamicLibrary.h"

DynamicLibrary::DynamicLibrary(const char* dllName)
{
	_module = LoadLibraryA(dllName);
}

DynamicLibrary::~DynamicLibrary()
{
	if (_module != NULL)
	{
		FreeLibrary(_module);
	}
}

bool DynamicLibrary::isLoaded() const
{
	return _module != NULL;
}

template<typename Function>
Function* DynamicLibrary::getFunction(const char* functionName) const
{
	if (isLoaded())
	{
		FARPROC functionAddress = GetProcAddress(_module, functionName);
		return (Function*)functionAddress;
	}
	return NULL;
}
