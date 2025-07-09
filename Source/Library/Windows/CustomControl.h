#pragma once

class CustomControl : public Control
{
	friend class Window;

protected:

	virtual void doCustomPaint(Graphics& graphics, bool disabled, bool selected);
};

