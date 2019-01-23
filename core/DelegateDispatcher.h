#pragma once
#include <list>
#include "Delegates.h"
#include "EventArgs.h"
#include "Timer.h"

using namespace std;

class DelegateDispatcher
{
public:
    DelegateDispatcher(Timer* pTimer);
    ~DelegateDispatcher();

	void	Process();

    void	Queue(float delay, Delegate* dlg, EventArgs args);

private:
    struct Dispatch
    {
        float tstamp;
        Delegate* toInvoke;
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

