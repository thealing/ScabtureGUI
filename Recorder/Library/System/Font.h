#pragma once

class Font : NonCopyable
{
	friend class Graphics;
	friend class Window;

public:

	Font(const wchar_t* name, int size, int weight);

	~Font();

private:

	HFONT _handle;
};

