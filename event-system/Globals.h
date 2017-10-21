#ifndef GLOBALS_H
#define GLOBALS_H
#include "Timer.h"
#include "EventDispatcher.h"
#include "DelegateDispatcher.h"
#include "Randomizer.h"
#include "Shader.h"

class Globals
{
public:
    static ViewPort         Screen;
    static float            PhysicalAspectRatio;
    static Timer            Clock;
    static EventDispatcher  CoreEvents;
    static DelegateDispatcher CoreDelegates;
    static Randomizer       Random;


    //static bool Init()    { }
    //static void DestroyAll()    { }

private:
    Globals();
};


#endif // GLOBALS_H