#include "Core.h"

Timer               Core::Clock;
DelegateDispatcher  Core::CoreDelegates( &Core::Clock);
EventDispatcher     Core::CoreEvents( &Core::Clock);
Randomizer          Core::Random;

Core::Core()
{

}
