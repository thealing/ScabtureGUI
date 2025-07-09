#include "DeviceIndicatorAdapter.h"

DeviceIndicatorAdapter::DeviceIndicatorAdapter(Window* parent, const Image* image) : DeviceIndicator(parent, image)
{
	_available = true;
	_active = true;
	updateStatus();
}

void DeviceIndicatorAdapter::setAvailable(bool available)
{
	if (_available != available)
	{
		_available = available;
		updateStatus();
	}
}

void DeviceIndicatorAdapter::setActive(bool active)
{
	if (_active != active)
	{
		_active = active;
		updateStatus();
	}
}

void DeviceIndicatorAdapter::updateStatus()
{
	if (_available && _active)
	{
		setStatus(DeviceStatusActive);
	}
	else if (!_available)
	{
		setStatus(DeviceStatusUnavailable);
	}
	else if (!_active)
	{
		setStatus(DeviceStatusInactive);
	}
}
