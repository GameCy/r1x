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
        Start( (*_target), 0);
    }

    void Start(T end, float _duration)
    {
        endValue = end;
        speed = endValue - (*target);
        Begin(_duration);
    }

    virtual void Update(float dt)
    {
        if (Time>Duration)
            return;

        Time+=dt;
        if (IsFinished())
            (*target) = endValue;
        else
            (*target) += (dt/Duration)*speed;
    }

private:
    T*      target;
    T       endValue;
    T       speed;
};

#include <QVector2D>
#include <QVector3D>
typedef Interpolator<float>     FloatInterpolator;
typedef Interpolator<QVector2D> QV2Interpolator;
typedef Interpolator<QVector3D> QV3Interpolator;

#endif // _INTERPOLATOR_H
