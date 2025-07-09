#include "MediaApplication.h"

MediaApplication::MediaApplication(bool console) : Application(console)
{
	initPlatform();
	setAccurateTimer();
	setDpiAwareness();
}

MediaApplication::~MediaApplication()
{
	uninitPlatform();
}

void MediaApplication::initPlatform()
{
	Status result;
	if (result)
	{
		result = CoInitialize(NULL);
	}
	if (result)
	{
		result = MFStartup(MF_VERSION);
	}
	if (!result)
	{
		LogUtil::logComError(__FUNCTION__, result);
	}
}

void MediaApplication::uninitPlatform()
{
	Status result = MFShutdown();
	if (!result)
	{
		LogUtil::logComError(__FUNCTION__, result);
	}
	CoUninitialize();
}

void MediaApplication::setAccurateTimer()
{
	double timerResolution = Timer::setResolution(0);
	LogUtil::logDebug(L"Changed timer resolution to %g.", timerResolution);
}

void MediaApplication::setDpiAwareness()
{
	BOOL result = SetProcessDPIAware();
	if (result == FALSE)
	{
		LogUtil::logWarning(L"Failed to set DPI awareness.");
	}
}
