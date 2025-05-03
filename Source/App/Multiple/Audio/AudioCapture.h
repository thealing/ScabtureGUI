#pragma once

class AudioCapture : public MediaSource
{
public:

	virtual ~AudioCapture();

	void setCallback(const Callback& callback);

protected:

	void invokeCallback();

private:

	Callback _callback;
};

