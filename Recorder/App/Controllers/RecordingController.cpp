#include "RecordingController.h"

RecordingController::RecordingController(MainWindow* mainWindow, RecordingManager* recordingManager, VideoCaptureManager* videoCaptureManager, VideoEncoderFactory* videoEncoderFactory, AudioCaptureManager* audioCaptureManager, AudioEncoderFactory* audioEncoderFactory, SinkWriterFactory* sinkWriterFactory,  MainSettingsManager* mainSettingsManager, SoundPlayer* soundPlayer, KeyboardListener* keyboardListener) : _eventDispatcher(mainWindow)
{
	_mainWindow = mainWindow;
	_recordingManager = recordingManager;
	_videoCaptureManager = videoCaptureManager;
	_videoEncoderFactory = videoEncoderFactory;
	_audioCaptureManager = audioCaptureManager;
	_audioEncoderFactory = audioEncoderFactory;
	_sinkWriterFactory = sinkWriterFactory;
	_mainSettingsManager = mainSettingsManager;
	_soundPlayer = soundPlayer;
	_keyboardListener = keyboardListener;
	RecordingPanel* recordingPanel = mainWindow->getRecordingPanel();
	_eventDispatcher.addEntry(recordingPanel->getStartClickEvent(), BIND(RecordingController, onStartButtonClicked, this));
	_eventDispatcher.addEntry(recordingPanel->getStopClickEvent(), BIND(RecordingController, onStopButtonClicked, this));
	_eventDispatcher.addEntry(recordingPanel->getPauseClickEvent(), BIND(RecordingController, onPauseButtonClicked, this));
	_eventDispatcher.addEntry(keyboardListener->getStartEvent(), BIND(RecordingController, onStartHotkeyPressed, this));
	_eventDispatcher.addEntry(keyboardListener->getStopEvent(), BIND(RecordingController, onStopHotkeyPressed, this));
	_eventDispatcher.addEntry(keyboardListener->getPauseEvent(), BIND(RecordingController, onPauseHotkeyPressed, this));
	_eventDispatcher.addEntry(keyboardListener->getResumeEvent(), BIND(RecordingController, onResumeHotkeyPressed, this));
	_eventDispatcher.start();
	LogUtil::logDebug(L"RecordingController: Started on thread %i.", _eventDispatcher.getThreadId());
}

RecordingController::~RecordingController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"RecordingController: Stopped.");
}

void RecordingController::onStartButtonClicked()
{
	LogUtil::logInfo(L"RecordingController: Start button clicked.");
	startRecording();
}

void RecordingController::onStopButtonClicked()
{
	LogUtil::logInfo(L"RecordingController: Stop button clicked.");
	stopRecording();
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
	stopRecording();
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

void RecordingController::startRecording()
{
	if (_recordingManager->isRunning())
	{
		LogUtil::logWarning(L"RecordingController: Cannot start recording because it is already running.");
		return;
	}
	LogUtil::logInfo(L"RecordingController: Starting recording.");
	SinkWriter* sinkWriter = _sinkWriterFactory->createSinkWriter();
	VideoCapture* videoCapture = _videoCaptureManager->lockCapture();
	Encoder* videoEncoder = _videoEncoderFactory->createEncoder(videoCapture, sinkWriter);
	AudioCapture* audioCapture = _audioCaptureManager->lockCapture();
	Encoder* audioEncoder = _audioEncoderFactory->createEncoder(audioCapture, sinkWriter);
	doActionsBeforeRecording();
	_soundPlayer->playStartSound();
	_recordingManager->start(sinkWriter, videoEncoder, audioEncoder);
	LogUtil::logInfo(L"RecordingController: Started recording.");
}

void RecordingController::stopRecording()
{
	if (!_recordingManager->isRunning())
	{
		LogUtil::logWarning(L"RecordingController: Cannot stop recording because it is not running.");
		return;
	}
	LogUtil::logInfo(L"RecordingController: Stopping recording.");
	_recordingManager->stop();
	_soundPlayer->playStopSound();
	doActionsAfterRecording();
	_recordingManager->cleanup();
	_videoCaptureManager->unlockCapture();
	_audioCaptureManager->unlockCapture();
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
	_soundPlayer->playPauseSound();
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
	_soundPlayer->playResumeSound();
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
	if (settings.askToPlayTheSavedRecording)
	{
		const wchar_t* path = _recordingManager->getPath();
		ShellExecute(NULL, L"open", path, NULL, NULL, SW_SHOWNORMAL);
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
