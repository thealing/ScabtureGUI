#include "ImageStore.h"

ImageStore& ImageStore::getInstance()
{
	static ImageStore instance;
	return instance;
}

Image* ImageStore::getStartImage()
{
	return _startImage;
}

Image* ImageStore::getPauseImage()
{
	return _pauseImage;
}

Image* ImageStore::getResumeImage()
{
	return _resumeImage;
}

Image* ImageStore::getStopImage()
{
	return _stopImage;
}

Image* ImageStore::getSettingsImage()
{
	return _settingsImage;
}

Image* ImageStore::getSpeakerImage()
{
	return _speakerImage;
}

Image* ImageStore::getMicrophoneImage()
{
	return _microphoneImage;
}

ImageStore::ImageStore()
{
	_startImage = new Image(ID_START);
	_pauseImage = new Image(ID_PAUSE);
	_resumeImage = new Image(ID_RESUME);
	_stopImage = new Image(ID_STOP);
	_settingsImage = new Image(ID_SETTINGS);
	_speakerImage = new Image(ID_SPEAKER);
	_microphoneImage = new Image(ID_MICROPHONE);
}
