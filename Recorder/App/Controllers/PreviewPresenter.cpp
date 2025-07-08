#include "PreviewPresenter.h"

PreviewPresenter::PreviewPresenter(PreviewDisplay* previewDisplay, VideoCaptureManager* videoCaptureManager, MainSettingsManager* mainSettingsManager, VideoSettingsManager* videoSettingsManager, RecordingManager* recordingManager)
{
	_previewDisplay = previewDisplay;
	_videoCaptureManager = videoCaptureManager;
	_mainSettingsManager = mainSettingsManager;
	_videoSettingsManager = videoSettingsManager;
	_recordingManager = recordingManager;
	_eventDispatcher.addEntry(videoCaptureManager->getChangeEvent(), BIND(PreviewPresenter, onFrame, this));
	_eventDispatcher.addEntry(videoCaptureManager->getFrameEvent(), BIND(PreviewPresenter, onFrame, this));
	_eventDispatcher.addEntry(videoCaptureManager->getErrorEvent(), BIND(PreviewPresenter, onError, this));
	_eventDispatcher.start();
}

PreviewPresenter::~PreviewPresenter()
{
	_eventDispatcher.stop();
}

void PreviewPresenter::onFrame()
{
	MainSettings mainSettings = _mainSettingsManager->getSettings();
	VideoSettings videoSettings = _videoSettingsManager->getSettings();
	bool recording = _recordingManager->isRunning();
	_previewDisplay->setDisabled(mainSettings.disablePreviewDuringRecording && recording);
	_previewDisplay->setHighQuality(mainSettings.highQualityPreview);
	_previewDisplay->setUpscale(!videoSettings.resize);
	VideoCapture* capture = _videoCaptureManager->lockCapture();
	if (capture != NULL)
	{
		const Buffer* buffer = capture->getBuffer();
		if (buffer != NULL)
		{
			_previewDisplay->setBuffer(*buffer);
		}
		_previewDisplay->setActive(true);
	}
	else
	{
		_previewDisplay->setActive(false);
	}
	_videoCaptureManager->unlockCapture();
	_previewDisplay->draw();
	DwmFlush();
}

void PreviewPresenter::onError()
{
	_previewDisplay->setActive(false);
}
