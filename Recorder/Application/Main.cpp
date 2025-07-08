#include "Main.h"

int main(int, char**)
{
	ScreenRecorderApplication application(true);
	application.run();
	return 0;
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	ScreenRecorderApplication application(false);
	application.run();
	return 0;
}
