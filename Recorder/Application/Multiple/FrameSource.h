#pragma once

class FrameSource : NonCopyable
{
public:

	virtual ~FrameSource();

	virtual const Event* getFrameEvent() = 0;

	virtual const Event* getErrorEvent() = 0;

	virtual void releaseFrameEvent(const Event* event) = 0;

	virtual void releaseErrorEvent(const Event* event) = 0;
};

