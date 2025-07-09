#pragma once

class Image : NonCopyable
{
	friend class Graphics;

public:

	Image(int width, int height, void* pixels);

	Image(int resourceId);

	~Image();

private:

	HBITMAP _bitmap;
	HDC _context;
};

