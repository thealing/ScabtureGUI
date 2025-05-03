#include "FontStore.h"

FontStore& FontStore::getInstance()
{
	static FontStore instance;
	return instance;
}

Font* FontStore::getPanelFont()
{
	return _panelFont;
}

Font* FontStore::getDisplayFont()
{
	return _displayFont;
}

FontStore::FontStore()
{
	_panelFont = new Font(L"Segoe UI", 16, FW_REGULAR);
	_displayFont = new Font(L"Verdana", 25, FW_REGULAR);
}
