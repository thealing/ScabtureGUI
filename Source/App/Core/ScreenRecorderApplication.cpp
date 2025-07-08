#include "ScreenRecorderApplication.h"

ScreenRecorderApplication::ScreenRecorderApplication(bool console) : MediaApplication(console)
{
}

void ScreenRecorderApplication::run()
{
	SourcePanel* sourcePanel = _mainWindow.getSourcePanel();
	SettingsPanel* settingsPanel = _mainWindow.getSettingsPanel();
	PreviewDisplay* previewDisplay = _mainWindow.getPreviewDisplay();
	FpsDisplay* fpsDisplay = _mainWindow.getFpsDisplay();
	RecordingPanel* recordingPanel = _mainWindow.getRecordingPanel();
	ResizePanel* resizePanel = _mainWindow.getResizePanel();
	QualityPanel* qualityPanel = _mainWindow.getQualityPanel();
	RecordingDisplay* recordingDisplay = _mainWindow.getRecordingDisplay();
	VolumeDisplay* volumeDisplay = _mainWindow.getVolumeDisplay();
	SourceController sourceController(sourcePanel, &_videoSourceManager, &_audioSourceManager);
	QualityController qualityController(qualityPanel, &_videoSettingsManager);
	ResizeController resizeController(resizePanel, &_videoCaptureManager, &_videoSettingsManager);
	AudioDeviceObserver audioDeviceObserver(&_audioDeviceProvider, &_audioVolumeListener, &_audioResamplerFactory);
	VideoCaptureController videoCaptureController(&_videoCaptureManager, &_windowCaptureFactory, &_screenCaptureFactory, &_videoResizerFactory, &_videoSourceManager, &_videoSettingsManager, &_keyboardListener);
	AudioCaptureController audioCaptureController(&_audioCaptureManager, &_audioResamplerFactory, &_audioDeviceProvider, &_audioSourceManager);
	MainSettingsController mainSettingsController(settingsPanel, &_mainSettingsDialog, &_mainSettingsManager);
	VideoSettingsController videoSettingsController(sourcePanel, &_videoSettingsDialog, &_videoSettingsManager);
	AudioSettingsController audioSettingsController(sourcePanel, &_audioSettingsDialog, &_audioSettingsManager);
	PreviewPresenter previewPresenter(previewDisplay, &_videoCaptureManager, &_mainSettingsManager, &_videoSettingsManager, &_recordingManager);
	FpsPresenter fpsPresenter(fpsDisplay, &_videoCaptureManager, &_recordingManager);
	RecordingPresenter recordingPresenter(recordingDisplay, &_recordingManager, &_videoCaptureManager);
	AudioPresenter audioPresenter(volumeDisplay, &_audioVolumeListener, &_audioSourceManager);
	UsagePresenter usagePresenter(settingsPanel, &_cpuMonitor, &_memoryMonitor);
	MainSettingsObserver mainSettingsObserver(&_mainWindow, &_mainSettingsManager, &_keyboardListener, &_sinkWriterFactory);
	VideoSettingsObserver videoSettingsObserver(&_videoSettingsManager, &_windowCaptureFactory, &_screenCaptureFactory, &_videoResizerFactory, &_videoEncoderFactory);
	AudioSettingsObserver audioSettingsObserver(&_audioSettingsManager, &_audioResamplerFactory, &_audioEncoderFactory);
	RecordingController recordingController(&_mainWindow, &_recordingManager, &_videoCaptureManager, &_videoEncoderFactory, &_audioCaptureManager, &_audioEncoderFactory, &_sinkWriterFactory, &_mainSettingsManager, &_keyboardListener);
	SnapshotController snapshotController(&_videoCaptureManager, &_keyboardListener);
	_mainWindow.runMessageLoop();
}
