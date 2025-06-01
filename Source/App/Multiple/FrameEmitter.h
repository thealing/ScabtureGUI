#pragma once

template<class Base>
class FrameEmitter : public Base
{
public:

	virtual const Event* getFrameEvent() override;

	virtual const Event* getErrorEvent() override;

	virtual void releaseFrameEvent(const Event* event) override;

	virtual void releaseErrorEvent(const Event* event) override;

protected:

	void signalFrame();

	void signalError();

private:

	EventPool _frameEventPool;
	EventPool _errorEventPool;
};

