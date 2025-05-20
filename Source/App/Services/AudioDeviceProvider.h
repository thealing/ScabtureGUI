#pragma once

class AudioDeviceProvider : IMMNotificationClient, NonCopyable
{
public:

	AudioDeviceProvider();

	virtual ~AudioDeviceProvider();

	AudioDevice* getInputDevice() const;

	AudioDevice* getOutputDevice() const;

	const Event* getInputChangeEvent() const;

	const Event* getOutputChangeEvent() const;

private:

	HRESULT GetDeviceName(LPCWSTR deviceId, PROPVARIANT* deviceName) const;

	virtual ULONG STDMETHODCALLTYPE AddRef() override;

	virtual ULONG STDMETHODCALLTYPE Release() override;

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) override;

	virtual HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState) override;

	virtual HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR pwstrDeviceId) override;

	virtual HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId) override;

	virtual HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDefaultDeviceId) override;

	virtual HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key) override;

private:

	Status _status;
	ComPointer<IMMDeviceEnumerator> _enumerator;
	EventPool _inputChangeEventPool;
	EventPool _outputChangeEventPool;
};

