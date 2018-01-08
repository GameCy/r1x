#ifndef _INTERPOLATOR_H
#define _INTERPOLATOR_H

template<class T>
class Interpolator
{
public:
    Interpolator(T* _target)
        : target(_target)
    {
        Start( (*_target), 0);
    }

    void Start(T end, float _duration)
    {
        t = 0;
        endValue = end;
        change = endValue - (*target);
        duration = _duration;
    }

    bool IsFinished()
    {
        return t>duration;
    }

    void Update(float dt)
    {
        if (t>duration)
            return;

        t += dt;
        if (t<duration)
            *target += (dt/duration)*change;
        else
            *target = endValue;
    }

private:
    T*      target;
    T       endValue;
    T       change;

    float   duration;
    float   t;
};

#include <QVector2D>
#include <QVector3D>
typedef Interpolator<float>     FloatInterpolator;
typedef Interpolator<QVector2D> QV2Interpolator;
typedef Interpolator<QVector3D> QV3Interpolator;

#endif // _INTERPOLATOR_H
