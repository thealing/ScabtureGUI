#pragma once

class RecordingController : NonCopyable
{
public:

	RecordingController(MainWindow* mainWindow, RecordingManager* recordingManager, VideoCaptureManager* videoCaptureManager, VideoEncoderFactory* videoEncoderFactory, AudioCaptureManager* audioCaptureManager, AudioEncoderFactory* audioEncoderFactory, SinkWriterFactory* sinkWriterFactory, MainSettingsManager* mainSettingsManager, KeyboardListener* keyboardListener);

	~RecordingController();

private:

	void onStartButtonClicked();
	
	void onStopButtonClicked();
	
	void onPauseButtonClicked();
	
	void onStartHotkeyPressed();
	
	void onStopHotkeyPressed();
	
	void onPauseHotkeyPressed();
	
	void onResumeHotkeyPressed();

	void startRecording();
	
	void stopRecording();
	
	void pauseRecording();
	
	void resumeRecording();

	void doActionsBeforeRecording();

	void doActionsAfterRecording();

	void updatePanel(bool recording, bool paused);

	void updateControls(bool recording);

	void onVideoError();

	void onAudioError();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<MainWindow> _mainWindow;
	WeakPointer<RecordingManager> _recordingManager;
	WeakPointer<VideoCaptureManager> _videoCaptureManager;
	WeakPointer<VideoEncoderFactory> _videoEncoderFactory;
	WeakPointer<AudioCaptureManager> _audioCaptureManager;
	WeakPointer<AudioEncoderFactory> _audioEncoderFactory;
	WeakPointer<SinkWriterFactory> _sinkWriterFactory;
	WeakPointer<MainSettingsManager> _mainSettingsManager;
	WeakPointer<KeyboardListener> _keyboardListener;
};

