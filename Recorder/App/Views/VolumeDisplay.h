#pragma once

class VolumeDisplay : public Frame
{
public:

	VolumeDisplay(Window* parent);

	void setInputAvailable(bool active);

	void setInputActive(bool active);

	void setOutputAvailable(bool active);

	void setOutputActive(bool active);

	void setInputVolumes(float leftVolume, float rightVolume);

	void setOutputVolumes(float leftVolume, float rightVolume);

private:

	UniquePointer<DeviceIndicatorAdapter> _inputIndicator;
	UniquePointer<DeviceIndicatorAdapter> _outputIndicator;
	UniquePointer<VolumeMeter> _inputVolumeMeter;
	UniquePointer<VolumeMeter> _outputVolumeMeter;
};

