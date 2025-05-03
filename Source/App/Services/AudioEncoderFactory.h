#pragma once

class AudioEncoderFactory : NonCopyable
{
public:

	AudioEncoderFactory();

	bool setSettings(const AudioEncoderSettings& settings);

	Encoder* createEncoder(AudioCapture* source, SinkWriter* sinkWriter) const;

private:

	AudioEncoderSettings _settings;
};

