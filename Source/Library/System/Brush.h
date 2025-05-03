#pragma once

class Brush : NonCopyable
{
	friend class Graphics;

public:

	Brush();

	Brush(Color color);

	~Brush();

private:

	HBRUSH _handle;
};

