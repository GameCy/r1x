#ifndef TEMPORAL_H
#define TEMPORAL_H
#include <list>

class Temporal
{
public:
    Temporal();
    virtual ~Temporal() {}

    inline void    Begin(float duration, int numRepeats=-1)
    {
        Time=0;
        Duration = duration;
        Repetitions = numRepeats;
    }

    inline void    Repeat(int numRepeats)   { Repetitions = numRepeats; }

    inline bool    IsFinished()    { return (Time>Duration) && (Repetitions==0); }
    inline bool    WasStarted()    { return Duration>0; }
    inline bool    IsForever()     { return Repetitions==-1; }

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

