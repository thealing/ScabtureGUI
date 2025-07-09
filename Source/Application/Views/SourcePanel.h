#pragma once

class SourcePanel : public Panel
{
public:

	SourcePanel(Window* parent);

	void setVideoSource(int source);

	void setAudioSource(int source);

	int getVideoSource() const;

	int getAudioSource() const;

	const Event* getVideoChangeEvent() const;

	const Event* getAudioChangeEvent() const;

	const Event* getVideoOptionsClickEvent() const;

	const Event* getAudioOptionsClickEvent() const;

private:

	void initVideoSources();

	void initAudioSources();

private:

	UniquePointer<Label> _videoSourceLabel;
	UniquePointer<Label> _audioSourceLabel;
	UniquePointer<ComboBox> _videoSourceList;
	UniquePointer<ComboBox> _audioSourceList;
	UniquePointer<Button> _videoSettingsButton;
	UniquePointer<Button> _audioSettingsButton;
};

