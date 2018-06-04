#ifndef TEMPORAL_H
#define TEMPORAL_H
#include <list>

class Temporal
{
public:
    Temporal();
    virtual ~Temporal() {}

    float   Duration;
    float   Time;

    inline void    Begin(float duration)    { Time=0; Duration = duration; }

    inline bool    IsFinished()    {  return Time>Duration; }

    virtual void Update(float dt);

    float TimeRatio();
};

class TemporalPool
{
public:
    static void Add(Temporal* tempo);
    static void Remove(Temporal* tempo);
    static void Update(float dt);

private:
    TemporalPool() {}

    static std::list<Temporal*> weakTemporals;
};

#endif // TEMPORAL_H

