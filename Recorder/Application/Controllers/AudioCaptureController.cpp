#include "AudioCaptureController.h"

AudioCaptureController::AudioCaptureController(AudioCaptureManager* audioCaptureManager, AudioResamplerFactory* audioResamplerFactory, AudioDeviceProvider* audioDeviceProvider, AudioSourceManager* audioSourceManager, MainWindow* mainWindow)
{
	_audioCaptureManager = audioCaptureManager;
	_audioResamplerFactory = audioResamplerFactory;
	_audioDeviceProvider = audioDeviceProvider;
	_audioSourceManager = audioSourceManager;
	_mainWindow = mainWindow;
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
	AudioSource source = _audioSourceManager->getSource();
	if (source == AudioSourceMicrophone)
	{
		updateCapture();
	}
}

void AudioCaptureController::onOutputDeviceChanged()
{
	LogUtil::logInfo(L"AudioCaptureController: Output device changed.");
	AudioSource source = _audioSourceManager->getSource();
	if (source == AudioSourceSystemOutput)
	{
		updateCapture();
	}
}

void AudioCaptureController::onResamplerChanged()
{
	LogUtil::logInfo(L"AudioCaptureController: Audio resampler changed.");
	AudioSource source = _audioSourceManager->getSource();
	if (source != AudioSourceNone)
	{
		updateCapture();
	}
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
	AudioCapture* capture = NULL;
	switch (source)
	{
		case AudioSourceNone:
		{
			_audioCaptureManager->setCapture(NULL);
			break;
		}
		case AudioSourceSystemOutput:
		{
			capture = _audioDeviceProvider->getOutputDevice();
			capture = _audioResamplerFactory->createResampler(capture);
			break;
		}
		case AudioSourceMicrophone:
		{
			capture = _audioDeviceProvider->getInputDevice();
			capture = _audioResamplerFactory->createResampler(capture);
			break;
		}
	}
	if (capture != NULL)
	{
		Status status = capture->getStatus();
		if (!status)
		{
			delete capture;
			_audioSourceManager->setSource(AudioSourceNone);
			UniquePointer<const wchar_t> errorMessage = StringUtil::formatString(L"Failed to start audio capture!\nError: 0x%08X", (HRESULT)status);
			_mainWindow->showMessageBox(L"Audio error", errorMessage, MB_OK | MB_ICONERROR);
			return;
		}
	}
	_audioCaptureManager->setCapture(capture);
	LogUtil::logInfo(L"AudioCaptureController: Updated capture.");
}

