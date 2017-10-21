#include "Globals.h"

ViewPort            Globals::Screen;
float               Globals::PhysicalAspectRatio=1.0f;

Timer               Globals::Clock;
DelegateDispatcher  Globals::CoreDelegates( &Globals::Clock);
EventDispatcher     Globals::CoreEvents( &Globals::Clock);
Randomizer          Globals::Random;

Globals::Globals()
{

}
