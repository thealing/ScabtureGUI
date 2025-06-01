#include "DataCombobox.h"

DataComboBox::DataComboBox(Window* parent, int* value, const wchar_t** options, int count) : ComboBox(parent)
{
	_value = value;
	setOptions(options, count);
	setSelection(*value);
#ifdef FUZZ_TESTING
	*_value = rand() % count;
#endif
}

void DataComboBox::onChange()
{
	ComboBox::onChange();
	*_value = getSelection();
}
