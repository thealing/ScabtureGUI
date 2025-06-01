#include "SinkWriterFactory.h"

SinkWriterFactory::SinkWriterFactory()
{
}

bool SinkWriterFactory::setSettings(const SinkWriterSettings& settings)
{
	return _settingsManager.setSettings(settings);
}

SinkWriter* SinkWriterFactory::createSinkWriter(const wchar_t* path)
{
	SinkWriterSettings settings = _settingsManager.getSettings();
	return new SinkWriter(settings, path);
}
