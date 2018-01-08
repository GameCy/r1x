#pragma once
#include <vector>
#include "Delegates.h"
#include "EventArgs.h"

typedef std::vector<EventArgs>	EventArgsVec;

class EventDispatcher;

class Event
{
public:
	Event(void);
	Event(Event*);
	~Event(void);

	void Subscribe(Delegate* observer);
	void Unsubscribe(Delegate* observer);

	void Notify(EventArgs args, float delay=0);
	void NotifyNow(EventArgs args);
	EventArgsVec CollectResponses(EventArgs args);

	DelegateList	mSubscribers;

	void SetDispatcher(EventDispatcher* dsp) { dispatcher = dsp; }
	void ClearDispatcher() { dispatcher = 0; }

private:
	EventDispatcher* dispatcher;
};

class ExpiringEvent : public Event
{
public:
    ExpiringEvent(EventDispatcher* dispatcher)
    {
        SetDispatcher(dispatcher);
    }

    void Start(float duration)
    {
        Notify(EventArgs("ExpireEvent",0), duration);
    }
};

