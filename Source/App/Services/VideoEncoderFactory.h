#pragma once

class VideoEncoderFactory : NonCopyable
{
public:

	VideoEncoderFactory();

	bool setSettings(const VideoEncoderSettings& settings);

	Encoder* createEncoder(VideoCapture* source, SinkWriter* sinkWriter) const;

private:

	VideoEncoderSettings _settings;
};

