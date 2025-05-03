#include "SinkWriterFactory.h"

SinkWriterFactory::SinkWriterFactory() : _settings()
{
}

bool SinkWriterFactory::setSettings(const SinkWriterSettings& settings)
{
	if (MemoryUtil::areEqual(_settings, settings))
	{
		return false;
	}
	_settings = settings;
	return true;
}

SinkWriter* SinkWriterFactory::createSinkWriter()
{
	const wchar_t* path = SaveUtil::generateFileName(L"Recording", L"mp4");
	return new SinkWriter(_settings, path);
}
