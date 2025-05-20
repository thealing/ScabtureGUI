#include "SinkWriterFactory.h"

SinkWriterFactory::SinkWriterFactory()
{
}

bool SinkWriterFactory::setSettings(const SinkWriterSettings& settings)
{
	return _settingsManager.setSettings(settings);
}

SinkWriter* SinkWriterFactory::createSinkWriter()
{
	SinkWriterSettings settings = _settingsManager.getSettings();
	const wchar_t* path = SaveUtil::generateFileName(L"Recording", L"mp4");
	return new SinkWriter(settings, path);
}
