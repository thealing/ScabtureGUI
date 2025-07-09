#pragma once

class Picture : public CustomControl
{
public:

	Picture(Window* parent, const Image* image);

	void setImage(const Image* image);

protected:

	virtual void doCustomPaint(Graphics& graphics, bool disabled, bool selected) override;

private:

	const Image* _image;
};

