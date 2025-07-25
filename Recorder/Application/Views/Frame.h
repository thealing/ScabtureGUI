#pragma once

class Frame : public Control
{
public:

	Frame(Window* parent);

protected:

	virtual void doPaint(Graphics& graphics) override;

private:

	UniquePointer<Pen> _borderPen;
};

