#include "SourcePanel.h"

SourcePanel::SourcePanel(Window* parent) : Panel(parent)
{
	setBounds(Rect(0, 0, 375, 65));
	_videoSourceLabel = new Label(this, L"Video Source: ");
	_videoSourceLabel->setBounds(Vector(12, 10), Vector(80, 20));
	_audioSourceLabel = new Label(this, L"Audio Source: ");
	_audioSourceLabel->setBounds(Vector(12, 35), Vector(80, 20));
	_videoSourceList = new ComboBox(this);
	_videoSourceList->setBounds(Vector(100, 10), Vector(150, 100));
	_audioSourceList = new ComboBox(this);
	_audioSourceList->setBounds(Vector(100, 35), Vector(150, 100));
	_videoSettingsButton = new Button(this, L"Video Options");
	_videoSettingsButton->setBounds(Vector(260, 10), Vector(100, 20));
	_audioSettingsButton = new Button(this, L"Audio Options");
	_audioSettingsButton->setBounds(Vector(260, 35), Vector(100, 20));
	FontStore& fontStore = FontStore::getInstance();
	setChildrenFont(fontStore.getPanelFont());
	initVideoSources();
	initAudioSources();
}

void SourcePanel::setVideoSource(int source)
{
	_videoSourceList->setSelection(source);
}

void SourcePanel::setAudioSource(int source)
{
	_audioSourceList->setSelection(source);
}

int SourcePanel::getVideoSource() const
{
	return _videoSourceList->getSelection();
}

int SourcePanel::getAudioSource() const
{
	return _audioSourceList->getSelection();
}

const Event* SourcePanel::getVideoChangeEvent() const
{
	return _videoSourceList->getSelectionEvent();
}

const Event* SourcePanel::getAudioChangeEvent() const
{
	return _audioSourceList->getSelectionEvent();
}

const Event* SourcePanel::getVideoOptionsClickEvent() const
{
    return _videoSettingsButton->getClickEvent();
}

const Event* SourcePanel::getAudioOptionsClickEvent() const
{
	return _audioSettingsButton->getClickEvent();
}

void SourcePanel::initVideoSources()
{
	const wchar_t* options[] = { L"Fullscreen", L"Rectangle", L"Window" };
	_videoSourceList->setOptions(options, ARRAYSIZE(options));
}

void SourcePanel::initAudioSources()
{
	const wchar_t* options[] = { L"None", L"System Output", L"Microphone", L"System + Microphone"};
	_audioSourceList->setOptions(options, ARRAYSIZE(options));
}
