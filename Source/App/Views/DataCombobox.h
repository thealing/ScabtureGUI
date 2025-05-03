#pragma once

class DataComboBox : public ComboBox
{
public:

	DataComboBox(Window* parent, int* value, const wchar_t** options, int count);

private:

	virtual void onChange() override;

private:

	int* _value;
};

