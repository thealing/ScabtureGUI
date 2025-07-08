#include "VolumeDisplay.h"

VolumeDisplay::VolumeDisplay(Window* parent) : Frame(parent)
{
	setAnchor(AnchorBottomLeft);
	setBounds(Vector(395, 0), Vector(200, 80));
	ImageStore& imageStore = ImageStore::getInstance();
	_inputIndicator = new DeviceIndicatorAdapter(this, imageStore.getMicrophoneImage());
	_inputIndicator->setBounds(Vector(8, 40), Vector(30, 30));
	_outputIndicator = new DeviceIndicatorAdapter(this, imageStore.getSpeakerImage());
	_outputIndicator->setBounds(Vector(8, 10), Vector(30, 30));
	_inputVolumeMeter = new VolumeMeter(this);
	_inputVolumeMeter->setBounds(Vector(46, 46), Vector(140, 18));
	_outputVolumeMeter = new VolumeMeter(this);
	_outputVolumeMeter->setBounds(Vector(46, 16), Vector(140, 18));
	FontStore& fontStore = FontStore::getInstance();
	setChildrenFont(fontStore.getDisplayFont());
}

void VolumeDisplay::setInputAvailable(bool available)
{
	_inputIndicator->setAvailable(available);
}

void VolumeDisplay::setInputActive(bool active)
{
	_inputIndicator->setActive(active);
}

void VolumeDisplay::setOutputAvailable(bool available)
{
	_outputIndicator->setAvailable(available);
}

void VolumeDisplay::setOutputActive(bool active)
{
	_outputIndicator->setActive(active);
}

void VolumeDisplay::setInputVolumes(float leftVolume, float rightVolume)
{
	_inputVolumeMeter->setVolumes(leftVolume, rightVolume);
}

void VolumeDisplay::setOutputVolumes(float leftVolume, float rightVolume)
{
	_outputVolumeMeter->setVolumes(leftVolume, rightVolume);
}
