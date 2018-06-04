#include "Temporal.h"
#include <QDebug>

Temporal::Temporal()
    : Duration(0.f)
    , Time(-1.f)
    , Repetitions(-1)
{}

void Temporal::Update(float dt)
{
    if(Duration>0.f)
        Time+=dt;

    if (IsFinished())
    {
        if (Repetitions!=0)
            Time=0;
        if (Repetitions>0)
            --Repetitions; // ToDo: emit Finished
    }
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
    qDebug() << "Temporals:" << weakTemporals.size();
}

void TemporalPool::Update(float dt)
{
    for(Temporal* tempo : weakTemporals)
        tempo->Update(dt);
}
