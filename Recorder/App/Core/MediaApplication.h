#pragma once

class MediaApplication : public Application
{
public:

	MediaApplication(bool console);

	~MediaApplication();

private:

	void initPlatform();

	void uninitPlatform();

	void setAccurateTimer();
};
