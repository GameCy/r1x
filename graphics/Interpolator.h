#ifndef _INTERPOLATOR_H
#define _INTERPOLATOR_H
#include "Temporal.h"

template<class T>
class Interpolator : public Temporal
{
public:
    Interpolator(T* _target)
        : target(_target)
    {
        TemporalPool::Add(this);
        endValue = *target;
        distance = endValue - (*target);
    }
    virtual ~Interpolator()     { TemporalPool::Remove(this); }

    void Start(T end, float _duration)
    {
        endValue = end;
        distance = endValue - (*target);
        Begin(_duration);
    }

    virtual void Update(float dt)
    {
        (*target) += (dt/Duration)*distance;
    }
    virtual bool Completed()
    {
        (*target) = endValue;
        return true;
    }

private:
    T*      target;
    T       endValue;
    T       distance;
};

#include <QVector2D>
#include <QVector3D>
typedef Interpolator<float>     FloatInterpolator;
typedef Interpolator<QVector2D> QV2Interpolator;
typedef Interpolator<QVector3D> QV3Interpolator;

#endif // _INTERPOLATOR_H
