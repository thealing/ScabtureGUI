#pragma once

class Button : public Control
{
public:

	Button(Window* parent, const wchar_t* text);

	const Event* getClickEvent() const;
};
