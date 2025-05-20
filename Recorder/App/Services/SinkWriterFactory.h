#pragma once

class SinkWriterFactory : NonCopyable
{
public:

	SinkWriterFactory();

	bool setSettings(const SinkWriterSettings& settings);

	SinkWriter* createSinkWriter();

private:

	AsyncSettingsManager<SinkWriterSettings> _settingsManager;
};

