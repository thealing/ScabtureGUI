#include "RecordingController.h"

RecordingController::RecordingController(MainWindow* mainWindow, RecordingManager* recordingManager, VideoCaptureManager* videoCaptureManager, VideoEncoderFactory* videoEncoderFactory, AudioCaptureManager* audioCaptureManager, AudioEncoderFactory* audioEncoderFactory, SinkWriterFactory* sinkWriterFactory, MainSettingsManager* mainSettingsManager, KeyboardListener* keyboardListener)
{
	_mainWindow = mainWindow;
	_recordingManager = recordingManager;
	_videoCaptureManager = videoCaptureManager;
	_videoEncoderFactory = videoEncoderFactory;
	_audioCaptureManager = audioCaptureManager;
	_audioEncoderFactory = audioEncoderFactory;
	_sinkWriterFactory = sinkWriterFactory;
	_mainSettingsManager = mainSettingsManager;
	_keyboardListener = keyboardListener;
	RecordingPanel* recordingPanel = mainWindow->getRecordingPanel();
	_eventDispatcher.addEntry(recordingPanel->getStartClickEvent(), BIND(RecordingController, onStartButtonClicked, this));
	_eventDispatcher.addEntry(recordingPanel->getStopClickEvent(), BIND(RecordingController, onStopButtonClicked, this));
	_eventDispatcher.addEntry(recordingPanel->getPauseClickEvent(), BIND(RecordingController, onPauseButtonClicked, this));
	_eventDispatcher.addEntry(keyboardListener->getStartEvent(), BIND(RecordingController, onStartHotkeyPressed, this));
	_eventDispatcher.addEntry(keyboardListener->getStopEvent(), BIND(RecordingController, onStopHotkeyPressed, this));
	_eventDispatcher.addEntry(keyboardListener->getPauseEvent(), BIND(RecordingController, onPauseHotkeyPressed, this));
	_eventDispatcher.addEntry(keyboardListener->getResumeEvent(), BIND(RecordingController, onResumeHotkeyPressed, this));
	_eventDispatcher.addEntry(recordingManager->getVideoErrorEvent(), BIND(RecordingController, onVideoError, this));
	_eventDispatcher.addEntry(recordingManager->getAudioErrorEvent(), BIND(RecordingController, onAudioError, this));
	_eventDispatcher.start(mainWindow);
	LogUtil::logDebug(L"RecordingController: Started on thread %i.", _eventDispatcher.getThreadId());
}

RecordingController::~RecordingController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"RecordingController: Stopped.");
	// In case the main window closes abruptly, we could get here while the recording is still running.
	// This would cause a deadlock in the capture controllers.
	// So then we must stop the recording here to prevent that from happening.
	if (_recordingManager->isRunning())
	{
		stopRecording(true); 
	}
}

void RecordingController::onStartButtonClicked()
{
	LogUtil::logInfo(L"RecordingController: Start button clicked.");
	startRecording();
}

void RecordingController::onStopButtonClicked()
{
	LogUtil::logInfo(L"RecordingController: Stop button clicked.");
	stopRecording(true); 
}

void RecordingController::onPauseButtonClicked()
{
	if (_recordingManager->isPaused())
	{
		LogUtil::logInfo(L"RecordingController: Resume button clicked.");
		resumeRecording();
	}
	else
	{
		LogUtil::logInfo(L"RecordingController: Pause button clicked.");
		pauseRecording();
	}
}

void RecordingController::onStartHotkeyPressed()
{
	LogUtil::logInfo(L"RecordingController: Start hotkey pressed.");
	startRecording();
}

void RecordingController::onStopHotkeyPressed()
{
	LogUtil::logInfo(L"RecordingController: Stop hotkey pressed.");
	stopRecording(true); 
}

void RecordingController::onPauseHotkeyPressed()
{
	LogUtil::logInfo(L"RecordingController: Pause hotkey pressed.");
	pauseRecording();
}

void RecordingController::onResumeHotkeyPressed()
{
	LogUtil::logInfo(L"RecordingController: Resume hotkey pressed.");
	resumeRecording();
}

void RecordingController::onVideoError()
{
	LogUtil::logError(L"RecordingController: Video recording failed.");
	// A video error just means that the target window was closed.
	// This might have been intentional, so we call this a success.
	stopRecording(true);
}

void RecordingController::onAudioError()
{
	LogUtil::logError(L"RecordingController: Audio recording failed.");
	// An audio error means that either the device was unplugged or some settings were changed.
	// This was probably unintentional, so we call this a failure.
	stopRecording(false); 
}

void RecordingController::startRecording()
{ 
	if (_recordingManager->isRunning())
	{
		LogUtil::logWarning(L"RecordingController: Cannot start recording because it is already running.");
		return;
	}
	LogUtil::logInfo(L"RecordingController: Starting recording.");
	const wchar_t* outputPath = FileUtil::generateRecordingSavePath();
	SinkWriter* sinkWriter = _sinkWriterFactory->createSinkWriter(outputPath);
	VideoCapture* videoCapture = _videoCaptureManager->lockCapture();
	Encoder* videoEncoder = _videoEncoderFactory->createEncoder(videoCapture, sinkWriter);
	AudioCapture* audioCapture = _audioCaptureManager->lockCapture();
	Encoder* audioEncoder = _audioEncoderFactory->createEncoder(audioCapture, sinkWriter);
	Status status = sinkWriter->getStatus();
	if (status)
	{
		doActionsBeforeRecording();
		_recordingManager->start(sinkWriter, videoEncoder, audioEncoder);
		_mainWindow->setOutputPath(outputPath);
		LogUtil::logInfo(L"RecordingController: Started recording.");
	}
	else
	{
		delete videoEncoder;
		delete audioEncoder;
		delete sinkWriter;
		delete outputPath;
		_videoCaptureManager->unlockCapture();
		_audioCaptureManager->unlockCapture();
		UniquePointer<const wchar_t> errorMessage = StringUtil::formatString(L"Failed to start the recording!\nError: 0x%08X", status);
		_mainWindow->showMessageBox(L"Recording failed", errorMessage, MB_OK | MB_ICONERROR);
	}
}

void RecordingController::stopRecording(bool success)
{
	if (!_recordingManager->isRunning())
	{
		LogUtil::logWarning(L"RecordingController: Cannot stop recording because it is not running.");
		return;
	}
	LogUtil::logInfo(L"RecordingController: Stopping recording.");
	_recordingManager->stop();
	_videoCaptureManager->unlockCapture();
	_audioCaptureManager->unlockCapture();
	MessageBeep(success ? MB_OK : MB_ICONERROR);
	doActionsAfterRecording();
	LogUtil::logInfo(L"RecordingController: Stopped recording.");
}

void RecordingController::pauseRecording()
{
	if (!_recordingManager->isRunning())
	{
		LogUtil::logWarning(L"RecordingController: Cannot pause recording because it is not running.");
		return;
	}
	if (_recordingManager->isPaused())
	{
		LogUtil::logWarning(L"RecordingController: Cannot pause recording because it is already paused.");
		return;
	}
	LogUtil::logInfo(L"RecordingController: Pausing recording.");
	_recordingManager->pause();
	updatePanel(true, true);
	LogUtil::logInfo(L"RecordingController: Paused recording.");
}

void RecordingController::resumeRecording()
{
	if (!_recordingManager->isRunning())
	{
		LogUtil::logWarning(L"RecordingController: Cannot resume recording because it is not running.");
		return;
	}
	if (!_recordingManager->isPaused())
	{
		LogUtil::logWarning(L"RecordingController: Cannot resume recording because it is not paused.");
		return;
	}
	LogUtil::logInfo(L"RecordingController: Resuming recording.");
	updatePanel(true, false);
	_recordingManager->resume();
	LogUtil::logInfo(L"RecordingController: Resumed recording.");
}

void RecordingController::doActionsBeforeRecording()
{
	MainSettings settings = _mainSettingsManager->getSettings();
	if (settings.windowVisibility == WindowVisibilityMinimized)
	{
		_mainWindow->showState(SW_MINIMIZE);
	}
	if (settings.windowVisibility == WindowVisibilityHidden)
	{
		_mainWindow->showState(SW_HIDE);
	}
	updatePanel(true, false);
	updateControls(true);
}

void RecordingController::doActionsAfterRecording()
{
	updatePanel(false, false);
	updateControls(false);
	MainSettings settings = _mainSettingsManager->getSettings();
	if (settings.windowVisibility != WindowVisibilityNormal)
	{
		_mainWindow->showState(SW_RESTORE);
	}
	if (settings.askToPlayTheRecording)
	{
		int result = _mainWindow->showMessageBox(L"Recording finished", L"Open the recorded video?", MB_YESNO | MB_ICONQUESTION);
		if (result == IDYES)
		{
			_mainWindow->openOutputFile();
		}
	} 
}

void RecordingController::updatePanel(bool recording, bool paused)
{
	RecordingPanel* recordingPanel = _mainWindow->getRecordingPanel();
	recordingPanel->setRecordingState(recording);
	recordingPanel->setPausedState(paused);
}

void RecordingController::updateControls(bool recording)
{
	_mainWindow->setCloseable(!recording);
	SettingsPanel* settingsPanel = _mainWindow->getSettingsPanel();
	settingsPanel->setEnabled(!recording);
	SourcePanel* sourcePanel = _mainWindow->getSourcePanel();
	ResizePanel* resizePanel = _mainWindow->getResizePanel();
	QualityPanel* qualityPanel = _mainWindow->getQualityPanel();
	PreviewDisplay* previewDisplay = _mainWindow->getPreviewDisplay();
	sourcePanel->setDisabled(recording);
	resizePanel->setDisabled(recording);
	qualityPanel->setDisabled(recording);
}
