#include "AngleInterpolator.h"
#include <math.h>

AngleInterpolator::AngleInterpolator(bool degrees)
    : current(0.f)
    , target(0.0f)
    , speed(1.0f)
    , positiveDirection(true)
{
    if (degrees)
    {
        HalfCircle = 180.f;
        FullCircle = 360.f;
    }
    else
    {
        HalfCircle = M_PI;
        FullCircle = 2.f*M_PI;
    }
}

bool AngleInterpolator::Init(float start, float end, float speed)
{
    this->speed = speed;
    current = start;
    target = end;
}

float AngleInterpolator::GetCurrent()
{
    return  current;
}

bool AngleInterpolator::IsPositive()
{
    bool clockwise=true;
    if (current>target) clockwise = false;
    if (fabs(current-target)>HalfCircle)
        return !clockwise;
    return clockwise;
}

bool AngleInterpolator::IsFinished()
{
    return (current==target);
}

void AngleInterpolator::SetNewTarget(float newTarget)
{
    target = newTarget;
    positiveDirection = IsPositive();
}

void AngleInterpolator::Update(float dt)
{
    if (IsFinished() )  return;

    if (positiveDirection)  current += speed*dt;
    else                    current -= speed*dt;
    while(current>FullCircle)   current -= FullCircle;
    while(current<0.f)        current += FullCircle;
    if (positiveDirection!=IsPositive())
        current = target;

}
