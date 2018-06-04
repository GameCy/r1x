#include "Temporal.h"

Temporal::Temporal()
    : Duration(-1)
    , Time(0)
{}





void Temporal::Update(float dt)
{
    if(Duration>0.f)
        Time+=dt;
}

float Temporal::TimeRatio()
{
    if (Time<0)            return -1.f;
    if (Time>Duration)     return 1.f;
    return Time/Duration;
}

// -----------------------------------------------
std::list<Temporal*> TemporalPool::weakTemporals;

void TemporalPool::Add(Temporal *tempo)
{
    weakTemporals.push_back(tempo);
}

void TemporalPool::Remove(Temporal *tempo)
{
    weakTemporals.remove(tempo);
}

void TemporalPool::Update(float dt)
{
    for(Temporal* tempo : weakTemporals)
        tempo->Update(dt);
}
