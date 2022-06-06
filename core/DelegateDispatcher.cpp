#include "DelegateDispatcher.h"
#include <stdarg.h>
#include <stdio.h>


DelegateDispatcher::DelegateDispatcher(Timer *pTimer)
    : timer(pTimer)
//	, _lock(0)
{
    CreateLock();
}

DelegateDispatcher::~DelegateDispatcher()
{
    DestroyLock();
}

void	DelegateDispatcher::Process()
{
    if (triggers.empty())	return;
    float t = timer->Time;
	DispatchList	pending;

	Unlock();
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
	Lock();

	for( itr = pending.begin(); itr!=pending.end(); ++itr)
	{
        itr->toInvoke->Invoke(itr->args);
	}
}

void	DelegateDispatcher::Queue(float delay, Delegate *dlg, QVariantMap args)
{
	Dispatch		ti;
    ti.tstamp	= timer->Time + delay;
    ti.toInvoke = dlg;
	ti.args = args;

	Lock();
        triggers.push_back(ti);
	Unlock();
}

