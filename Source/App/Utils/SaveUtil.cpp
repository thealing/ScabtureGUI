#include "SaveUtil.h"

const wchar_t* SaveUtil::generateFileName(const wchar_t* label, const wchar_t* extension)
{
	wchar_t* fileName = new wchar_t[MAX_PATH];
#if _DEBUG
	swprintf(fileName, MAX_PATH, L"%ls.%ls", label, extension);
#else
	Date date;
	getDate(&date);
	swprintf(fileName, MAX_PATH, L"%ls %02hi %02hi %02hi %02hi %02hi %02hi.%ls", label, date.year % 100, date.month, date.day, date.hour, date.minute, date.second, extension);
#endif
	return fileName;
}
