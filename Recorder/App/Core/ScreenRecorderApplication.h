#pragma once

class ScreenRecorderApplication : public MediaApplication
{
public:

	ScreenRecorderApplication(bool console);

	void run();

private:

	VideoSourceManager _videoSourceManager;
	AudioSourceManager _audioSourceManager;
	KeyboardListener _keyboardListener;
	CpuMonitor _cpuMonitor;
	MemoryMonitor _memoryMonitor;
	WindowSourceManager _windowSourceManager;
	AudioDeviceProvider _audioDeviceProvider;
	AudioVolumeListener _audioVolumeListener;
	VideoCaptureManager _videoCaptureManager;
	AudioCaptureManager _audioCaptureManager;
	SinkWriterFactory _sinkWriterFactory;
	VideoResizerFactory _videoResizerFactory;
	AudioResamplerFactory _audioResamplerFactory;
	VideoEncoderFactory _videoEncoderFactory;
	AudioEncoderFactory _audioEncoderFactory;
	RecordingManager _recordingManager;
	MainSettingsManager _mainSettingsManager;
	VideoSettingsManager _videoSettingsManager;
	AudioSettingsManager _audioSettingsManager;
	MainSettingsDialog _mainSettingsDialog;
	VideoSettingsDialog _videoSettingsDialog;
	AudioSettingsDialog _audioSettingsDialog;
	MainWindow _mainWindow;
};

