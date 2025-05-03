#include "AudioDeviceObserver.h"

AudioDeviceObserver::AudioDeviceObserver(AudioDeviceProvider* audioDeviceProvider, AudioVolumeListener* audioVolumeListener)
{
	_audioDeviceProvider = audioDeviceProvider;
	_audioVolumeListener = audioVolumeListener;
	_eventDispatcher.addEntry(audioDeviceProvider->getInputChangeEvent(), BIND(AudioDeviceObserver, onInputDeviceChanged, this));
	_eventDispatcher.addEntry(audioDeviceProvider->getOutputChangeEvent(), BIND(AudioDeviceObserver, onOutputDeviceChanged, this));
	_eventDispatcher.start();
	LogUtil::logDebug(L"AudioDeviceObserver: Started on thread %i.", _eventDispatcher.getThreadId());
}

AudioDeviceObserver::~AudioDeviceObserver()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"AudioDeviceObserver: Stopped.");
}

void AudioDeviceObserver::onInputDeviceChanged()
{
	LogUtil::logInfo(L"AudioDeviceObserver: Input device changed.");
	AudioVolumeMeter* meter = _audioDeviceProvider->getInputVolumeMeter();
	_audioVolumeListener->setInputVolumeMeter(meter);
}

void AudioDeviceObserver::onOutputDeviceChanged()
{
	LogUtil::logInfo(L"AudioDeviceObserver: Output device changed.");
	AudioVolumeMeter* meter = _audioDeviceProvider->getOutputVolumeMeter();
	_audioVolumeListener->setOutputVolumeMeter(meter);
}

