#include "VideoEncoderFactory.h"

VideoEncoderFactory::VideoEncoderFactory() : _settings()
{
}

bool VideoEncoderFactory::setSettings(const VideoEncoderSettings& settings)
{
	if (MemoryUtil::areEqual(_settings, settings))
	{
		return false;
	}
	_settings = settings;
	return true;
}

Encoder* VideoEncoderFactory::createEncoder(VideoCapture* source, SinkWriter* sinkWriter) const
{
	return new VideoEncoder(_settings, source, sinkWriter);
}
