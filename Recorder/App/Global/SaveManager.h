#pragma once

class SaveManager : NonCopyable
{
public:

	static SaveManager& getInstance();

	bool loadBytes(const wchar_t* name, int count, void* bytes);

	bool saveBytes(const wchar_t* name, int count, const void* bytes);

	bool loadString(const wchar_t* name, const wchar_t** string);

	bool saveString(const wchar_t* name, const wchar_t* string);

private:

	SaveManager();

	~SaveManager();

private:

	HKEY _key;
};

