#include "AudioCaptureController.h"

AudioCaptureController::AudioCaptureController(AudioCaptureManager* audioCaptureManager, AudioResamplerFactory* audioResamplerFactory, AudioDeviceProvider* audioDeviceProvider, AudioSourceManager* audioSourceManager)
{
	_audioCaptureManager = audioCaptureManager;
	_audioResamplerFactory = audioResamplerFactory;
	_audioDeviceProvider = audioDeviceProvider;
	_audioSourceManager = audioSourceManager;
	_eventDispatcher.addEntry(audioResamplerFactory->getChangeEvent(), BIND(AudioCaptureController, onResamplerChanged, this));
	_eventDispatcher.addEntry(audioDeviceProvider->getInputChangeEvent(), BIND(AudioCaptureController, onInputDeviceChanged, this));
	_eventDispatcher.addEntry(audioDeviceProvider->getOutputChangeEvent(), BIND(AudioCaptureController, onOutputDeviceChanged, this));
	_eventDispatcher.addEntry(audioSourceManager->getChangeEvent(), BIND(AudioCaptureController, onSourceChanged, this));
	_eventDispatcher.addEntry(audioCaptureManager->getErrorEvent(), BIND(AudioCaptureController, onCaptureError, this));
	_eventDispatcher.start();
	LogUtil::logDebug(L"AudioCaptureController: Started on thread %i.", _eventDispatcher.getThreadId());
}

AudioCaptureController::~AudioCaptureController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"AudioCaptureController: Stopped.");
}

void AudioCaptureController::onInputDeviceChanged()
{
	LogUtil::logInfo(L"AudioCaptureController: Input device changed.");
	updateCapture();
}

void AudioCaptureController::onOutputDeviceChanged()
{
	LogUtil::logInfo(L"AudioCaptureController: Output device changed.");
	updateCapture();
}

void AudioCaptureController::onResamplerChanged()
{
	LogUtil::logInfo(L"AudioCaptureController: Audio resampler changed.");
	updateCapture();
}

void AudioCaptureController::onSourceChanged()
{
	LogUtil::logInfo(L"AudioCaptureController: Audio source changed.");
	updateCapture();
}

void AudioCaptureController::onCaptureError()
{
	LogUtil::logInfo(L"AudioCaptureController: Audio capture failed.");
	updateCapture();
}

void AudioCaptureController::updateCapture()
{
	LogUtil::logInfo(L"AudioCaptureController: Updating capture.");
	AudioSource source = _audioSourceManager->getSource();
#ifdef FUZZ_TESTING
	source = (AudioSource)(rand()%2+1);
#endif
	switch (source)
	{
		case AudioSourceNone:
		{
			_audioCaptureManager->setCapture(NULL);
			break;
		}
		case AudioSourceSystemOutput:
		{
			AudioDevice* device = _audioDeviceProvider->getOutputDevice();
			AudioCapture* resampler = _audioResamplerFactory->createResampler(device);
			_audioCaptureManager->setCapture(resampler);
			break;
		}
		case AudioSourceMicrophone:
		{
			AudioDevice* device = _audioDeviceProvider->getInputDevice();
			AudioCapture* resampler = _audioResamplerFactory->createResampler(device);
			_audioCaptureManager->setCapture(resampler);
			break;
		}
	}
	LogUtil::logInfo(L"AudioCaptureController: Updated capture.");
}

