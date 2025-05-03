#include "DataCheckbox.h"

DataCheckBox::DataCheckBox(Window* parent, bool* value) : CheckBox(parent, NULL)
{
	_value = value;
	setChecked(*value);
}

void DataCheckBox::onChange()
{
	CheckBox::onChange();
	*_value = getChecked();
}
