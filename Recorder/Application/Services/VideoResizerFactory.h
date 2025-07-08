#pragma once

class VideoResizerFactory : NonCopyable
{
public:

	VideoResizerFactory();

	const Event* getChangeEvent();

	bool setSettings(const VideoResizerSettings& settings);

	VideoCapture* createResizer(VideoCapture* source) const;

private:

	Resizer* createResizer(Vector inputSize, Vector outputSize) const;

private:

	AsyncSettingsManager<VideoResizerSettings> _settingsManager;
};

