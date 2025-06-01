#include "AudioPresenter.h"

AudioPresenter::AudioPresenter(VolumeDisplay* volumeDisplay, AudioVolumeListener* audioVolumeListener, AudioSourceManager* audioSourceManager)
{
	_volumeDisplay = volumeDisplay;
	_audioVolumeListener = audioVolumeListener;
	_audioSourceManager = audioSourceManager;
	_eventDispatcher.addEntry(audioVolumeListener->getUpdateEvent(), BIND(AudioPresenter, onUpdate, this));
	_eventDispatcher.addEntry(audioSourceManager->getSelectionEvent(), BIND(AudioPresenter, onSelection, this));
	_eventDispatcher.start(volumeDisplay);
}

AudioPresenter::~AudioPresenter()
{
	_eventDispatcher.stop();
}

void AudioPresenter::onUpdate()
{
	updateInputState();
	updateOutputState();
}

void AudioPresenter::onSelection()
{
	AudioSource source = _audioSourceManager->getSource();
	switch (source)
	{
		case AudioSourceNone:
		{
			_volumeDisplay->setInputActive(false);
			_volumeDisplay->setOutputActive(false);
			break;
		}
		case AudioSourceSystemOutput:
		{
			_volumeDisplay->setInputActive(false);
			_volumeDisplay->setOutputActive(true);
			break;
		}
		case AudioSourceMicrophone:
		{
			_volumeDisplay->setInputActive(true);
			_volumeDisplay->setOutputActive(false);
			break;
		}
		case AudioSourceSystemAndMicrophone:
		{
			_volumeDisplay->setInputActive(true);
			_volumeDisplay->setOutputActive(true);
			break;
		}
	}
}

void AudioPresenter::updateInputState()
{
	Volumes volumes = {};
	bool available = _audioVolumeListener->getInputVolumes(&volumes);
	_volumeDisplay->setInputAvailable(available);
	_volumeDisplay->setInputVolumes(volumes.left, volumes.right);
}

void AudioPresenter::updateOutputState()
{
	Volumes volumes = {};
	bool available = _audioVolumeListener->getOutputVolumes(&volumes);
	_volumeDisplay->setOutputAvailable(available);
	_volumeDisplay->setOutputVolumes(volumes.left, volumes.right);
}
