#pragma once

class DataCheckBox : public CheckBox
{
public:

	DataCheckBox(Window* parent, bool* value);

private:

	virtual void onChange() override;

private:

	bool* _value;
};

