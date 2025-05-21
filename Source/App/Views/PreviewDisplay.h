#pragma once

class PreviewDisplay : public Control
{
public:

	PreviewDisplay(Window* parent);

	void draw();

	void setDisabled(bool disabled);

	void setHighQuality(bool highQuality);

	void setUpscale(bool upscale);

	void setBuffer(const Buffer& buffer);

private:

	void updateControl();

	void moveControl(int x, int y, int width, int height);

	void drawPreview(Graphics& graphics);

	void drawPreviewDisabled(Graphics& graphics);

	virtual void onResize() override;

	virtual void doPaint(Graphics& graphics) override;

private:

	ExclusiveLock _lock;
	bool _dirty;
	bool _disabled;
	bool _highQuality;
	bool _upscale;
	int _width;
	int _height;
	int _stride;
	uint32_t* _pixels;
};

