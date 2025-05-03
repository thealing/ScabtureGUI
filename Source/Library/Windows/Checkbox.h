#pragma once

class CheckBox : public Control
{
public:

	CheckBox(Window* parent, const wchar_t* text);

	void setChecked(bool checked);

	bool getChecked();

	const Event* getCheckEvent() const;
};
