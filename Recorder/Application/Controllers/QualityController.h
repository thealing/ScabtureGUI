#pragma once

class QualityController : NonCopyable
{
public:

	QualityController(QualityPanel* qualityPanel, VideoSettingsManager* videoSettingsManager);

	~QualityController();

private:

	void onFrameRateChanged();

	void onBitRateChanged();

	void onVideoSettingsChanged();

private:

	WindowEventDispatcher _eventDispatcher;
	WeakPointer<QualityPanel> _qualityPanel;
	WeakPointer<VideoSettingsManager> _videoSettingsManager;
};

