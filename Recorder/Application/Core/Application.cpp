#include "Application.h"

Application::Application(bool console)
{
	LogUtil::init(console);
	LogUtil::logInfo(L"Application started.");
}

Application::~Application()
{
	LogUtil::logInfo(L"Application shut down.");
}
