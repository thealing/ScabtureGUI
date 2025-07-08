#pragma once

template<class Base>
class FrameDelegate : public Base
{
public:

	FrameDelegate(FrameSource* source);

	virtual const Event* getFrameEvent() override;

	virtual const Event* getErrorEvent() override;

	virtual void releaseFrameEvent(const Event* event) override;

	virtual void releaseErrorEvent(const Event* event) override;

private:

	WeakPointer<FrameSource> _source;
};

