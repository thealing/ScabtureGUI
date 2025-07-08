#pragma once

class DeviceIndicator : public Picture
{
public:

	DeviceIndicator(Window* parent, const Image* image);

	void setStatus(DeviceStatus status);

protected:

	virtual void doCustomPaint(Graphics& graphics, bool disabled, bool selected) override;

private:

	void drawCrossLine(Graphics& graphics, Color color, int width);

private:

	DeviceStatus _status;
};