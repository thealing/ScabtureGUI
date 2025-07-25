#pragma once

class MainWindow : public CustomWindow
{
public:

	MainWindow();

	void openOutputFile();

	void setOutputPath(const wchar_t* path);

	void setCloseable(bool closeable);

	void setTopMost(bool topMost);

	void excludeFromCapture(bool exclude);

	SourcePanel* getSourcePanel() const;

	ResizePanel* getResizePanel() const;

	QualityPanel* getQualityPanel() const;

	FpsDisplay* getFpsDisplay() const;

	RecordingPanel* getRecordingPanel() const;

	RecordingDisplay* getRecordingDisplay() const;

	SettingsPanel* getSettingsPanel() const;

	PreviewDisplay* getPreviewDisplay() const;

	VolumeDisplay* getVolumeDisplay() const;

protected:

	virtual bool canClose() override;

	virtual Vector getMinimumSize() override;

private:

	UniquePointer<SourcePanel> _sourcePanel;
	UniquePointer<ResizePanel> _resizePanel;
	UniquePointer<QualityPanel> _qualityPanel;
	UniquePointer<FpsDisplay> _fpsDisplay;
	UniquePointer<RecordingPanel> _recordingPanel;
	UniquePointer<RecordingDisplay> _recordingDisplay;
	UniquePointer<SettingsPanel> _settingsPanel;
	UniquePointer<PreviewDisplay> _previewDisplay;
	UniquePointer<VolumeDisplay> _volumeDisplay;
	UniquePointer<const wchar_t> _outputPath;
	bool _closeable;
};
