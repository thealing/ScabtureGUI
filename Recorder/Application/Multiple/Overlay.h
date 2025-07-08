#pragma once

class Overlay : NonCopyable
{
public:

	virtual ~Overlay();

	virtual void draw(uint32_t* pixels, int width, int height, int stride) = 0;
};
