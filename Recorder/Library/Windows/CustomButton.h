#pragma once

class CustomButton : public CustomControl
{
public:

	CustomButton(Window* parent, const Image* image);

	void setImage(const Image* image);

	const Event* getClickEvent() const;

protected:

	virtual void doCustomPaint(Graphics& graphics, bool disabled, bool selected) override;

private:

	const Image* _image;
};

