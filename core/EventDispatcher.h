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

	void	QueueNotify(float delay, Event evt, EventArgs args);

private:
    struct Dispatch
    {
        float tstamp;
        Event toRaise;
        EventArgs args;
    };

    typedef list<Dispatch>			DispatchList;
    typedef	DispatchList::iterator	DispatchListItr;

    DispatchList    triggers;
    Timer*          timer;
    //s3eThreadLock *_lock;
    void    CreateLock()	{ } //if (!_lock)  _lock = s3eThreadLockCreate(); }
    void    DestroyLock()	{ } //if (_lock)  s3eThreadLockDestroy(_lock); }
    void	Lock()			{ } //if (_lock)  s3eThreadLockAcquire(_lock, -1); }
    void	Unlock()		{ } //if (_lock)  s3eThreadLockRelease(_lock); }
};

