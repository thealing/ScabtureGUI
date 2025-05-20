#include "VideoEncoderFactory.h"

VideoEncoderFactory::VideoEncoderFactory()
{
}

bool VideoEncoderFactory::setSettings(const VideoEncoderSettings& settings)
{
	return _settingsManager.setSettings(settings);
}

Encoder* VideoEncoderFactory::createEncoder(VideoCapture* source, SinkWriter* sinkWriter) const
{
	VideoEncoderSettings settings = _settingsManager.getSettings();
	return new VideoEncoder(settings, source, sinkWriter);
}
