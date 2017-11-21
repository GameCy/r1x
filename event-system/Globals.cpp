#include "Globals.h"

ViewPort            Globals::Screen;
DPIHelper           Globals::DPI;

Timer               Globals::Clock;
DelegateDispatcher  Globals::CoreDelegates( &Globals::Clock);
EventDispatcher     Globals::CoreEvents( &Globals::Clock);
Randomizer          Globals::Random;

Globals::Globals()
{

}
