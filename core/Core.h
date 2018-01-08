#ifndef COREGLOBALS_H
#define COREGLOBALS_H
#include "Timer.h"
#include "EventDispatcher.h"
#include "DelegateDispatcher.h"
#include "Randomizer.h"

class Core
{
public:
    static Timer            Clock;
    static EventDispatcher  CoreEvents;
    static DelegateDispatcher CoreDelegates;
    static Randomizer       Random;

private:
    Core();
};


#endif // COREGLOBALS_H
