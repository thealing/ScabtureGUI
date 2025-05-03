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

void* DynamicLibrary::getFunction(const char* functionName) const
{
	if (!isLoaded())
	{
		return NULL;
	}
	FARPROC functionAddress = GetProcAddress(_module, functionName);
	return (void*)functionAddress;
}
