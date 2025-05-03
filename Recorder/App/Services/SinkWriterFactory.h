#pragma once

class SinkWriterFactory : NonCopyable
{
public:

	SinkWriterFactory();

	bool setSettings(const SinkWriterSettings& settings);

	SinkWriter* createSinkWriter();

private:

	SinkWriterSettings _settings;
};

