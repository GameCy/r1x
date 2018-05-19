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

/*
NICE ALTERNATIVE C++11 FOR EVENTS. NO NEED FOR DELEGATES, dispatcher can be optional

#include <vector>
template<typename... ARGS>
class Event
{
public:
    typedef std::function<void (ARGS)> Func;

public:
    void Call( ARGS arg )
    {
        for( auto f : handlers)
        {
            (f)( arg );
        }
    }

    void operator ()(T1 arg)
    {
        Call( arg );
    }

    Event& operator += ( Func f )
    {
        handlers.push_back( f );
        return *this;
    }

    Event& operator -= ( Func f )
    {
        for( auto i = m_handlers.begin(); i != m_handlers.end(); i++ )
        {
            if ( (*i).target<void (T1)>() == f.target<void (T1)>() )
            {
                handlers.erase( i );
                break;
            }
        }

        return *this;
    }

private:
    std::vector<Func> handlers;
};

*/
