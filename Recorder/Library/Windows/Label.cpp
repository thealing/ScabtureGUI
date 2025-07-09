#include "Label.h"

Label::Label(Window* parent, const wchar_t* text)
{
	create(L"STATIC", text, SS_CENTERIMAGE, parent);
}

Label::Label(Window* parent, const wchar_t* text, int align)
{
	long style = getAlignedstyle(align);
	create(L"STATIC", text, style, parent);
}

long Label::getAlignedstyle(int align)
{
	switch (align)
	{
		case AlignLeft:
		{
			return SS_CENTERIMAGE | SS_LEFT;
		}
		case AlignCenter:
		{
			return SS_CENTERIMAGE | SS_CENTER;
		}
		case AlignRight:
		{
			return SS_CENTERIMAGE | SS_RIGHT;
		}
		default:
		{
			return 0;
		}
	}
}
