#include "AudioVolumeMeter.h"

AudioVolumeMeter::AudioVolumeMeter(IMMDeviceEnumerator* enumerator, EDataFlow flow, ERole role)
{
	if (enumerator == NULL)
	{
		_status = E_INVALIDARG;
	}
	if (_status)
	{
		_status = enumerator->GetDefaultAudioEndpoint(flow, role, &_device);
	}
	if (_status)
	{
		_status = _device->Activate(__uuidof(IAudioMeterInformation), CLSCTX_ALL, NULL, (void**)&_meter);
	}
	if (!_status)
	{
		LogUtil::logComWarning("AudioVolumeMeter", _status);
	}
}

HRESULT AudioVolumeMeter::getVolumes(Volumes* volumes) const
{
	Status result;
	UINT count = 0;
	float values[2] = {};
	if (_meter == NULL)
	{
		result = E_POINTER;
	}
	if (result)
	{
		result = _meter->GetMeteringChannelCount(&count);
		count = min(count, 2u);
	}
	if (result)
	{
		result = _meter->GetChannelsPeakValues(count, values);
	}
	if (result)
	{
		if (count >= 1)
		{
			volumes->left = values[0];
			volumes->right = values[0];
		}
		if (count >= 2)
		{
			volumes->left = values[0];
			volumes->right = values[1];
		}
	}
	return result;
}
