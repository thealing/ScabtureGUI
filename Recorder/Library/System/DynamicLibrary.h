#pragma once

class DynamicLibrary : NonCopyable
{
public:

	DynamicLibrary(const char* dllName);

	~DynamicLibrary();

	bool isLoaded() const;

	template<typename Function>
	Function* getFunction(const char* functionName) const;

private:

	HMODULE _module;
};
