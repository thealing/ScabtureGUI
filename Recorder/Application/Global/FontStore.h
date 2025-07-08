#pragma once

class FontStore : NonCopyable
{
public:

	static FontStore& getInstance();

	Font* getPanelFont();

	Font* getDisplayFont();

private:

	FontStore();

private:

	UniquePointer<Font> _panelFont;
	UniquePointer<Font> _displayFont;
	UniquePointer<Font> _dialogFont;
};

