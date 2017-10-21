#include "Events.h"
#include "EventDispatcher.h"
#include <stdio.h>

Event::Event(void)
	:dispatcher(0)
{}
Event::Event(Event* other)
{
	dispatcher = other->dispatcher;
	mSubscribers = other->mSubscribers;
}

Event::~Event(void) 
{
	mSubscribers.clear();
}

void Event::Subscribe(Delegate* observer)		{	mSubscribers.push_back(observer); }

void Event::Unsubscribe(Delegate* observer)		{ 	mSubscribers.remove(observer); }

void Event::Notify(EventArgs args, float delay)
{
	if (dispatcher)
		dispatcher->QueueNotify(delay, Event(this), args);
	else
        NotifyNow(args);
}

void Event::NotifyNow(EventArgs args)
{
	DelegateListItr itr;
	for(itr=mSubscribers.begin(); itr!=mSubscribers.end(); ++itr)
	{
		(*itr)->Invoke(args);
	}
}

EventArgsVec Event::CollectResponses(EventArgs args)
{
	EventArgsVec results;
	results.reserve(mSubscribers.size());

	DelegateListItr itr;
	for(itr=mSubscribers.begin(); itr!=mSubscribers.end(); ++itr)
	{
		EventArgs itemArgs = args;
		(*itr)->Invoke(itemArgs);
		results.push_back(itemArgs);
	}
	return results;
}

