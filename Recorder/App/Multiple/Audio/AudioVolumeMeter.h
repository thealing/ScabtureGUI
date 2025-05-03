#pragma once

class AudioVolumeMeter : NonCopyable
{
public:

	AudioVolumeMeter(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role);

	HRESULT getVolumes(Volumes* volumes) const;

private:

	Status _status;
	ComPointer<IMMDevice> _device;
	ComPointer<IAudioMeterInformation> _meter;
};

