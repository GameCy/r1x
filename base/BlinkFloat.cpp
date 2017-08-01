#include "BlinkFloat.h"

BlinkFloat::BlinkFloat(float start, float end, float period)
    : startValue(start)
    , endValue(end)
    , duration(period)
    , current(0)
    , t(0)
{
}

void BlinkFloat::Update(float dt)
{
    t += dt;
    while(t>duration)
        t -= duration;
    float factor = t/duration;
    if (factor>.5f)
        factor = 1.f - factor;
    current =  endValue*factor + startValue*(1.f-factor);
}

float BlinkFloat::Value()
{
    return current;
}

void BlinkFloat::SetNewTarget(float newTarget)
{
    endValue = newTarget;
}
