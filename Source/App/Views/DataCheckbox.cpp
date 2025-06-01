#include "DataCheckbox.h"

DataCheckBox::DataCheckBox(Window* parent, bool* value) : CheckBox(parent, NULL)
{
	_value = value;
#ifdef FUZZ_TESTING
	*_value = rand() % 2;
#endif
	setChecked(*value);
}

void DataCheckBox::onChange()
{
	CheckBox::onChange();
	*_value = getChecked();
}
