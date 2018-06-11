#include "Temporal.h"
#include <QDebug>


std::list<Temporal*> TemporalPool::weakTemporals;

/*
 * temporals on stack can use Add() and Remove()
 * temporals on heap can use Add() and deleteLater()
*/

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
    auto itr = weakTemporals.begin();
    while(itr!=weakTemporals.end())
    {
        Temporal* tempo = (*itr);
        if (tempo->toDelete)
        {
            delete tempo;
            itr = weakTemporals.erase(itr);
        }
        else
        {
            if (tempo->IsStarted())
                tempo->Time += dt;
            tempo->Update(dt);
            ++itr;
        }
    }
}

void TemporalPool::DestroyAll()
{
    for(Temporal* tempo : weakTemporals)
    {
        delete tempo;
    }
}
