#include "FileUtil.h"

const wchar_t* FileUtil::generateRecordingSavePath()
{
	PWSTR videosFolder = NULL;
	SHGetKnownFolderPath(FOLDERID_Videos, 0, NULL, &videosFolder);
	UniquePointer<const wchar_t> path = StringUtil::formatString(L"%ls\\Scabture", videosFolder);
	CoTaskMemFree(videosFolder);
	SHCreateDirectory(NULL, path);
	return generateFilePath(path, L"Recording", L"mp4");
}

const wchar_t* FileUtil::generateSnapshotSavePath()
{
	PWSTR picturesFolder = NULL;
	SHGetKnownFolderPath(FOLDERID_Pictures, 0, NULL, &picturesFolder);
	UniquePointer<const wchar_t> path = StringUtil::formatString(L"%ls\\Scabture", picturesFolder);
	CoTaskMemFree(picturesFolder);
	SHCreateDirectory(NULL, path);
	return generateFilePath(path, L"Snapshot", L"png");
}

const wchar_t* FileUtil::generateFilePath(const wchar_t* directory, const wchar_t* label, const wchar_t* extension)
{
#if _DEBUG
	return StringUtil::formatString(L"%ls.%ls", label, extension);
#else
	Date date = getDate();
	return StringUtil::formatString(L"%ls\\%ls %04i-%02i-%02i %02i-%02i-%02i.%ls", directory, label, date.year, date.month, date.day, date.hour, date.minute, date.second, extension);
#endif
}
