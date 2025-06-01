#pragma once

class FileUtil
{
public:

	static const wchar_t* generateRecordingFilePath();

	static const wchar_t* generateSnapshotFilePath();

private:

	static const wchar_t* generateFilePath(const wchar_t* directory, const wchar_t* label, const wchar_t* extension);
};

