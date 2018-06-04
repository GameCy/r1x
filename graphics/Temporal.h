#ifndef TEMPORAL_H
#define TEMPORAL_H
#include <list>

class Temporal
{
public:
    Temporal();
    virtual ~Temporal() {}


    inline void    Begin(float duration)    { Time=0; Duration = duration; }
    inline void    Repeat(int numRepeats)   { Repetitions = numRepeats; }

    inline bool    IsFinished()    {  return Time>Duration; }

    virtual void Update(float dt);

    float TimeRatio();

protected:
    float   Duration;
    float   Time;
    int     Repetitions;
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

