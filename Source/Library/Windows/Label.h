#pragma once

class Label : public Control
{
public:

	enum : int
	{
		AlignLeft,
		AlignCenter,
		AlignRight,
		AlignCount
	};

public:

	Label(Window* parent, const wchar_t* text);

	Label(Window* parent, const wchar_t* text, int align);

private:

	static long getAlignedstyle(int align);
};

