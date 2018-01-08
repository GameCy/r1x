#include "BlinkFloat.h"

BlinkFloat::BlinkFloat(float start, float end, float period)
    : startValue(start)
    , endValue(end)
    , duration(period)
    , current(start)
    , t(0)
    , repetitions(1)
{
}

void BlinkFloat::Update(float dt)
{
    t += dt;
    while( (repetitions>0) && (t>duration) )
    {
        --repetitions;
        t -= duration;
    }
    if (repetitions<=0)
    {
        current = startValue;
    }
    else
    {
        float factor = 2.f*t/duration;
        if (factor>1.0f)
            factor = (2.f - factor);
        current =  endValue*factor + startValue*(1.f-factor);
    }
}

float BlinkFloat::Value()
{
    return current;
}

void BlinkFloat::SetNewTarget(float newTarget)
{
    endValue = newTarget;
}

bool BlinkFloat::hasEnded()
{
    return (repetitions<=0) && (t>duration);
}

void BlinkFloat::Repeat(int _repetitions)
{
    t=0;
    current = startValue;
    repetitions = _repetitions;
}
