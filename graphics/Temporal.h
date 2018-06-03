#ifndef TEMPORAL_H
#define TEMPORAL_H

class Temporal
{
public:
    Temporal()
        : Duration(-1)
        , Time(0)
    {}

    float   Duration;
    float   Time;

    void    Begin(float duration)  { Time=0; Duration = duration; }
    bool    IsFinished()    { return Time>Duration; }

    virtual void Update(float dt)
    {
        if(Duration>0.f)
            Time+=dt;
    }

    float TimeRatio()
    {
        if (Time<0)            return -1.f;
        if (Time>Duration)     return 1.f;
        return Time/Duration;
    }
};

#endif // TEMPORAL_H
