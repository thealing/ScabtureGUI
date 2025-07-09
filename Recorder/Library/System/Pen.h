#pragma once

class Pen : NonCopyable
{
	friend class Graphics;

public:

	Pen(Color color, int width);

	~Pen();

private:

	HPEN _handle;
};

