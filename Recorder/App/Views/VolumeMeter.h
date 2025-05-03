#pragma once

class VolumeMeter : public Control
{
public:

	VolumeMeter(Window* parent);

	~VolumeMeter();

	void setVolumes(float leftVolume, float rightVolume);

protected:

	virtual void onResize() override;

	virtual void doPaint(Graphics& graphics) override;

private:

	UniquePointer<Image> _image;
	float _leftVolume;
	float _rightVolume;
};

