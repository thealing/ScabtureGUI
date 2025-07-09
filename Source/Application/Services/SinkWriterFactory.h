#pragma once

class SinkWriterFactory : NonCopyable
{
public:

	SinkWriterFactory();

	bool setSettings(const SinkWriterSettings& settings);

	SinkWriter* createSinkWriter(const wchar_t* path);

private:

	AsyncSettingsManager<SinkWriterSettings> _settingsManager;
};

