#pragma once

class Graphics : NonCopyable
{
	friend class Window;

public:

	Graphics(HDC handle);

	void setTextColor(Color color);

	void setBackgroundColor(Color color);

	void setBrush(const Brush& brush);

	void setPen(const Pen& pen);

	void setFont(const Font& font);

	void drawLine(const Line& line);

	void drawRect(const Rect& rect);

	void drawString(const wchar_t* string, Alignment alignment, Vector position, Vector size);

	void drawImage(const Image& image, Vector position);

	void blendImage(const Image& image, Vector position, int alpha);

	void fillRect(const Rect& rect, const Brush& brush);

	void clear(Color color);

	HDC getHandle() const;

private:

	HDC _handle;

private:

	static UINT getAlignmentFormat(Alignment alignment);
};

