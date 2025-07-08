#pragma once

class DeviceIndicatorAdapter : public DeviceIndicator
{
public:

	DeviceIndicatorAdapter(Window* parent, const Image* image);

	void setAvailable(bool available);

	void setActive(bool active);

private:

	void updateStatus();

private:

	bool _available;
	bool _active;
};

