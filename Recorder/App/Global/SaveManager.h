#pragma once

class SaveManager : NonCopyable
{
public:

	static SaveManager& getInstance();

	bool loadData(const wchar_t* name, int count, void* data);

	bool saveData(const wchar_t* name, int count, const void* data);

private:

	SaveManager();

	~SaveManager();

private:

	HKEY _key;
};

