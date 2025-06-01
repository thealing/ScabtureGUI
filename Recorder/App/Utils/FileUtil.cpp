#include "FileUtil.h"

const wchar_t* FileUtil::generateRecordingFilePath()
{
	return generateFilePath(L".", L"Recording", L"mp4");
}

const wchar_t* FileUtil::generateSnapshotFilePath()
{
	return generateFilePath(L".", L"Snapshot", L"png");
}

const wchar_t* FileUtil::generateFilePath(const wchar_t* directory, const wchar_t* label, const wchar_t* extension)
{
#if _DEBUG
	return StringUtil::formatString(L"%ls.%ls", label, extension);
#else
	Date date = getDate();
	return StringUtil::formatString(L"%ls\\%ls %02hi %02hi %02hi %02hi %02hi %02hi.%ls", directory, label, date.year % 100, date.month, date.day, date.hour, date.minute, date.second, extension);
#endif
}
