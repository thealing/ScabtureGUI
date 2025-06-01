#pragma once

class CustomWindow : public Window
{
public:

	CustomWindow(const wchar_t* className);

	~CustomWindow();

private:

	ATOM _atom;
};

