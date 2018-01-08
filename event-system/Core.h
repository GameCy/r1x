#ifndef GLOBALS_H
#define GLOBALS_H
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


#endif // GLOBALS_H
