#pragma once

class EventDispatcher : public EventDispatcherBase
{
public:

	EventDispatcher();

	~EventDispatcher();

	void addEntry(const Event* event, const Callback& callback);

protected:

	virtual void onEvent(int index) override;

protected:

	Callback* _callbacks;
};

