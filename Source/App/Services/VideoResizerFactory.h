#pragma once

class VideoResizerFactory : NonCopyable
{
public:

	VideoResizerFactory();

	bool setSettings(const VideoResizerSettings& settings);

	VideoCapture* createResizer(VideoCapture* source) const;

	const Event* getChangeEvent() const;

private:

	Resizer* createResizer(Vector inputSize, Vector outputSize) const;

private:

	VideoResizerSettings _settings;
	EventPool _changeEventPool;
};

