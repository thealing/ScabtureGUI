#pragma once

class ImageStore : NonCopyable
{
public:

	static ImageStore& getInstance();

	Image* getStartImage();

	Image* getPauseImage();

	Image* getResumeImage();

	Image* getStopImage();

	Image* getSettingsImage();

	Image* getSpeakerImage();

	Image* getMicrophoneImage();

private:

	ImageStore();

private:

	UniquePointer<Image> _startImage;
	UniquePointer<Image> _pauseImage;
	UniquePointer<Image> _resumeImage;
	UniquePointer<Image> _stopImage;
	UniquePointer<Image> _settingsImage;
	UniquePointer<Image> _speakerImage;
	UniquePointer<Image> _microphoneImage;
};

