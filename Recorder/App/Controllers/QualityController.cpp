#include "QualityController.h"

QualityController::QualityController(QualityPanel* qualityPanel, VideoSettingsManager* videoSettingsManager)
{
	_qualityPanel = qualityPanel;
	_videoSettingsManager = videoSettingsManager;
	_eventDispatcher.addEntry(qualityPanel->getFrameRateChangeEvent(), BIND(QualityController, onFrameRateChanged, this));
	_eventDispatcher.addEntry(qualityPanel->getBitRateChangeEvent(), BIND(QualityController, onBitRateChanged, this));
	_eventDispatcher.addEntry(videoSettingsManager->getChangeEvent(), BIND(QualityController, onVideoSettingsChanged, this));
	_eventDispatcher.start(qualityPanel);
	LogUtil::logDebug(L"QualityController: Started on thread %i.", _eventDispatcher.getThreadId());
}

QualityController::~QualityController()
{
	_eventDispatcher.stop();
	LogUtil::logDebug(L"QualityController: Stopped.");
}

void QualityController::onFrameRateChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	int frameRate = _qualityPanel->getFrameRate();
	if (settings.frameRate != frameRate)
	{
		LogUtil::logInfo(L"QualityController: Framerate modified to %i.", frameRate);
		settings.frameRate = frameRate;
		_videoSettingsManager->setSettings(settings);
	}
}

void QualityController::onBitRateChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	int bitRate = _qualityPanel->getBitRate();
	if (settings.bitRate != bitRate)
	{
		LogUtil::logInfo(L"QualityController: Bitrate modified to %i.", bitRate);
		settings.bitRate = bitRate;
		_videoSettingsManager->setSettings(settings);
	}
}

void QualityController::onVideoSettingsChanged()
{
	VideoSettings settings = _videoSettingsManager->getSettings();
	int visibleFrameRate = _qualityPanel->getFrameRate();
	if (settings.frameRate != visibleFrameRate)
	{
		LogUtil::logInfo(L"QualityController: Framerate setting changed to %i.", settings.frameRate);
		_qualityPanel->setFrameRate(settings.frameRate);
	}
	int visibleBitRate = _qualityPanel->getBitRate();
	if (settings.bitRate != visibleBitRate)
	{
		LogUtil::logInfo(L"QualityController: Bitrate setting changed to %i.", settings.bitRate);
		_qualityPanel->setBitRate(settings.bitRate);
	}
}
