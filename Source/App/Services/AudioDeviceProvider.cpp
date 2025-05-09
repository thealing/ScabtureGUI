#include "AudioDeviceProvider.h"

AudioDeviceProvider::AudioDeviceProvider()
{
	if (_status)
	{
		_status = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, IID_PPV_ARGS(&_enumerator));
	}
	if (_status)
	{
		_status = _enumerator->RegisterEndpointNotificationCallback(this);
	}
	if (_status)
	{
		_inputChangeEventPool.setEvents();
		_outputChangeEventPool.setEvents();
	}
	if (!_status)
	{
		LogUtil::logComWarning("AudioDeviceProvider", _status);
	}
}

AudioDeviceProvider::~AudioDeviceProvider()
{
	if (_status)
	{
		_enumerator->UnregisterEndpointNotificationCallback(this);
	}
}

AudioCapture* AudioDeviceProvider::getInputCapture() const
{
	return new AudioDevice(_enumerator, eCapture, eConsole);
}

AudioCapture* AudioDeviceProvider::getOutputCapture() const
{
	return new AudioDevice(_enumerator, eRender, eConsole);
}

AudioVolumeMeter* AudioDeviceProvider::getInputVolumeMeter() const
{
	return new AudioVolumeMeter(_enumerator, eCapture, eConsole);
}

AudioVolumeMeter* AudioDeviceProvider::getOutputVolumeMeter() const
{
	return new AudioVolumeMeter(_enumerator, eRender, eConsole);
}

const Event* AudioDeviceProvider::getInputChangeEvent() const
{
	return _inputChangeEventPool.getEvent();
}

const Event* AudioDeviceProvider::getOutputChangeEvent() const
{
	return _outputChangeEventPool.getEvent();
}

HRESULT AudioDeviceProvider::GetDeviceName(LPCWSTR deviceId, PROPVARIANT* deviceName) const
{
	Status result;
	ComPointer<IMMDevice> device;
	ComPointer<IPropertyStore> propertyStore;
	if (deviceId == NULL)
	{
		result = E_INVALIDARG;
	}
	if (deviceName == NULL)
	{
		result = E_INVALIDARG;
	}
	if (result)
	{
		result = _enumerator->GetDevice(deviceId, &device);
	}
	if (result)
	{
		result = device->OpenPropertyStore(STGM_READ, &propertyStore);
	}
	if (result)
	{
		result = propertyStore->GetValue(PKEY_Device_FriendlyName, deviceName);
	}
	if (!result)
	{
		LogUtil::logComWarning(__FUNCTION__, result);
	}
	return result;
}

ULONG __stdcall AudioDeviceProvider::AddRef()
{
	return 0;
}

ULONG __stdcall AudioDeviceProvider::Release()
{
	return 0;
}

HRESULT __stdcall AudioDeviceProvider::QueryInterface(REFIID riid, void** ppvObject)
{
	if (riid == __uuidof(IUnknown))
	{
		*ppvObject = this;
		return S_OK;
	}
	if (riid == __uuidof(IMMNotificationClient))
	{
		*ppvObject = this;
		return S_OK;
	}
	*ppvObject = NULL;
	return E_NOINTERFACE;
}

HRESULT __stdcall AudioDeviceProvider::OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState)
{
	const wchar_t* pszState = NULL;
	switch (dwNewState)
	{
		case DEVICE_STATE_ACTIVE:
		{
			pszState = L"ACTIVE";
			break;
		}
		case DEVICE_STATE_DISABLED:
		{
			pszState = L"DISABLED";
			break;
		}
		case DEVICE_STATE_NOTPRESENT:
		{
			pszState = L"NOTPRESENT";
			break;
		}
		case DEVICE_STATE_UNPLUGGED:
		{
			pszState = L"UNPLUGGED";
			break;
		}
	}
	PropVariant deviceName;
	GetDeviceName(pwstrDeviceId, &deviceName);
	LogUtil::logDebug(L"AudioDeviceProvider: State of device \"%ls\" changed to %ls.", deviceName->pwszVal, pszState);
	return S_OK;
}

HRESULT __stdcall AudioDeviceProvider::OnDeviceAdded(LPCWSTR pwstrDeviceId)
{
	PropVariant deviceName;
	GetDeviceName(pwstrDeviceId, &deviceName);
	LogUtil::logDebug(L"AudioDeviceProvider: Added device \"%ls\".", deviceName->pwszVal);
	return S_OK;
}

HRESULT __stdcall AudioDeviceProvider::OnDeviceRemoved(LPCWSTR pwstrDeviceId)
{
	PropVariant deviceName;
	GetDeviceName(pwstrDeviceId, &deviceName);
	LogUtil::logDebug(L"AudioDeviceProvider: Removed device \"%ls\".", deviceName->pwszVal);
	return S_OK;
}

HRESULT __stdcall AudioDeviceProvider::OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDefaultDeviceId)
{
	PropVariant deviceName;
	GetDeviceName(pwstrDefaultDeviceId, &deviceName);
	LogUtil::logDebug(L"AudioDeviceProvider: Default device of flow %i role %i changed to \"%ls\".", flow, role, deviceName->pwszVal);
	if (flow == eRender && role == eConsole)
	{
		LogUtil::logInfo(L"AudioDeviceProvider: Default output device changed to \"%ls\".", deviceName->pwszVal);
		_outputChangeEventPool.setEvents();
	}
	if (flow == eCapture && role == eConsole)
	{
		LogUtil::logInfo(L"AudioDeviceProvider: Default input device changed to \"%ls\".", deviceName->pwszVal);
		_inputChangeEventPool.setEvents();
	}
	return S_OK;
}

HRESULT __stdcall AudioDeviceProvider::OnPropertyValueChanged(LPCWSTR, const PROPERTYKEY)
{
	return S_OK;
}
