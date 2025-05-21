#include "PreviewPresenter.h"

PreviewPresenter::PreviewPresenter(PreviewDisplay* previewDisplay, VideoCaptureManager* videoCaptureManager, MainSettingsManager* mainSettingsManager, VideoSettingsManager* videoSettingsManager, RecordingManager* recordingManager)
{
	_previewDisplay = previewDisplay;
	_videoCaptureManager = videoCaptureManager;
	_mainSettingsManager = mainSettingsManager;
	_videoSettingsManager = videoSettingsManager;
	_recordingManager = recordingManager;
	_eventDispatcher.addEntry(videoCaptureManager->getFrameEvent(), BIND(PreviewPresenter, updatePreview, this));
	_eventDispatcher.start();
}

PreviewPresenter::~PreviewPresenter()
{
	_eventDispatcher.stop();
}

void PreviewPresenter::updatePreview()
{
	MainSettings mainSettings = _mainSettingsManager->getSettings();
	VideoSettings videoSettings = _videoSettingsManager->getSettings();
	bool recording = _recordingManager->isRunning();
	_previewDisplay->setDisabled(mainSettings.disablePreview && recording);
	_previewDisplay->setHighQuality(mainSettings.highQualityPreview);
	_previewDisplay->setUpscale(!videoSettings.doResize);
	VideoCapture* capture = _videoCaptureManager->lockCapture();
	if (capture != NULL)
	{
		const Buffer* buffer = capture->getBuffer();
		if (buffer != NULL)
		{
			_previewDisplay->setBuffer(*buffer);
		}
	}
	_videoCaptureManager->unlockCapture();
	_previewDisplay->invalidate();
	DwmFlush();
}
