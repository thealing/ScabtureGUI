#include "Panel.h"

Panel::Panel(Window* parent) : Frame(parent)
{
}

void Panel::setDisabled(bool disabled)
{
	setChildrenEnabled(!disabled);
}
