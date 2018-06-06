#ifndef TEMPORAL_H
#define TEMPORAL_H
#include <list>

class Temporal
{
public:
    Temporal();
    virtual ~Temporal() {}

    inline void    Begin(float duration=-1.f)
    {
        Time=0;
        Duration = duration;
    }

    inline bool    IsFinished()    { return Time>Duration; }
    inline bool    IsForever()     { return Duration<0.f; }

    float TimeRatio();
    virtual void Update(float dt);

protected:
    float   Duration;
    float   Time;
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

