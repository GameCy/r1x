#ifndef TEMPORAL_H
#define TEMPORAL_H
#include <list>

class Temporal;

class TemporalPool
{
public:
    static void Add(Temporal* tempo);
    static void Remove(Temporal* tempo);
    static void Update(float dt);
    static void DestroyAll();

private:
    TemporalPool() {}

    static std::list<Temporal*> weakTemporals;
};

// -------------------------------

class Temporal
{
public:
    Temporal()
        : Duration(-1.f)
        , Time(-1.f)
        , toDelete(false)
    { }

    virtual ~Temporal()   {}

    virtual void Update(float dt)=0;

    inline void    Begin(float duration=-1.f)
    {
        Time=0;
        Duration = duration;
    }

    inline bool IsFinished()    { return Duration>=0.f && Time>Duration; }
    inline bool IsStarted()     { return Time>=0.f; }
    inline bool IsForever()     { return Duration<0.f; }
    inline void deleteLater()   { toDelete=true; }

    inline float TimeRatio()
    {
        if (Time<0)             return 0.f;
        if (Time>Duration)      return 1.f;
        if (Duration<0.00001f)  return 0.f;
        return Time/Duration;
    }

    friend class TemporalPool;
protected:
    float   Duration;
    float   Time;
    bool    toDelete;
};


#endif // TEMPORAL_H

