#pragma once
#include <list>
#include "Events.h"
#include "Timer.h"

using namespace std;


class EventDispatcher
{
public:
    EventDispatcher(Timer* pTimer);
	~EventDispatcher(void);

	void	Process();

    void	QueueNotify(float delay, Event evt, QVariantMap args);

private:
    struct Dispatch
    {
        float tstamp;
        Event toRaise;
        QVariantMap args;
    };

    typedef list<Dispatch>			DispatchList;
    typedef	DispatchList::iterator	DispatchListItr;

    DispatchList    triggers;
    Timer*          timer;

};

