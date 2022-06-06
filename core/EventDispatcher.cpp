#include "EventDispatcher.h"
#include <stdarg.h>
#include <stdio.h>


EventDispatcher::EventDispatcher(Timer *pTimer)
    : timer(pTimer)
{
}

EventDispatcher::~EventDispatcher(void)
{
}

void	EventDispatcher::Process()
{
    if (triggers.size()==0)	return;
    float t = timer->Time;
	DispatchList	pending;

    DispatchListItr itr=triggers.begin();
    while(itr!=triggers.end())
	{
		if (itr->tstamp<=t)
		{
			pending.push_back(*itr);
            itr = triggers.erase(itr);
		}
		else	itr++;
	}

	for( itr = pending.begin(); itr!=pending.end(); ++itr)
	{
		itr->toRaise.NotifyNow(itr->args);
	}
}

void	EventDispatcher::QueueNotify(float delay, Event evt, QVariantMap args)
{
    Dispatch ti;
    ti.tstamp  = timer->Time + delay;
	ti.toRaise = evt;
    ti.args    = args;

    triggers.push_back(ti);
}

