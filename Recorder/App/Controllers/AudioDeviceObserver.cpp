#include "AudioDeviceObserver.h"

AudioDeviceObserver::AudioDeviceObserver(AudioDeviceProvider* audioDeviceProvider, AudioVolumeListener* audioVolumeListener, AudioResamplerFactory* audioResamplerFactory)
{
	_audioDeviceProvider = audioDeviceProvider;
	_audioVolumeListener = audioVolumeListener;
	_audioResamplerFactory = audioResamplerFactory;
	_eventDispatcher.addEntry(audioDeviceProvider->getInputChangeEvent(), BIND(AudioDeviceObserver, onInputDeviceChanged, this));
	_eventDispatcher.addEntry(audioDeviceProvider->getOutputChangeEvent(), BIND(AudioDeviceObserver, onOutputDeviceChanged, this));
	_eventDispatcher.addEntry(audioResamplerFactory->getChangeEvent(), BIND(AudioDeviceObserver, onResamplerChanged, this));
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
	updateInputDevice();
}

void AudioDeviceObserver::onOutputDeviceChanged()
{
	LogUtil::logInfo(L"AudioDeviceObserver: Output device changed.");
	updateOutputDevice();
}

void AudioDeviceObserver::onResamplerChanged()
{
	LogUtil::logInfo(L"AudioDeviceObserver: Resampler changed.");
	updateInputDevice();
	updateOutputDevice();
}

void AudioDeviceObserver::updateInputDevice()
{
	AudioDevice* device = _audioDeviceProvider->getInputDevice();
	AudioResampler* resampler = _audioResamplerFactory->createResampler(device);
	AudioVolumeMeter* meter = new AudioVolumeMeter(resampler);
	_audioVolumeListener->setInputVolumeMeter(meter);
}

void AudioDeviceObserver::updateOutputDevice()
{
	AudioDevice* device = _audioDeviceProvider->getOutputDevice();
	AudioResampler* resampler = _audioResamplerFactory->createResampler(device);
	AudioVolumeMeter* meter = new AudioVolumeMeter(resampler);
	_audioVolumeListener->setOutputVolumeMeter(meter);
}

