#include "Temporal.h"
#include <QDebug>

Temporal::Temporal()
    : Duration(-1.f)
    , Time(0)
{}

void Temporal::Update(float dt)
{
    if(IsFinished())
        return;
     Time+=dt;
}

float Temporal::TimeRatio()
{
    if (Time<0)             return 0.f;
    if (Time>Duration)      return 1.f;
    if (Duration<0.00001f)  return 0.f;
    return Time/Duration;
}

// -----------------------------------------------
std::list<Temporal*> TemporalPool::weakTemporals;

void TemporalPool::Add(Temporal *tempo)
{
    weakTemporals.push_back(tempo);
    qDebug() << "Temporals+:" << weakTemporals.size();
}

void TemporalPool::Remove(Temporal *tempo)
{
    weakTemporals.remove(tempo);
    qDebug() << "Temporals-:" << weakTemporals.size();
}

void TemporalPool::Update(float dt)
{
    for(Temporal* tempo : weakTemporals)
        tempo->Update(dt);
}
