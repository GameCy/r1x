#ifndef _INTERPOLATOR_H
#define _INTERPOLATOR_H
#include "Temporal.h"
#include "Delegates.h"

template<class T>
class Interpolator : public Temporal
{
public:
    Interpolator(T* _target)
        : target(_target)
        , Finished(0)
    {
        TemporalPool::Add(this);
        endValue = *target;
        distance = endValue - (*target);
    }
    virtual ~Interpolator()
    {
        if (toDelete==false)
            TemporalPool::Remove(this);
    }

    void Start(T end, float _duration, Delegate* finished=0)
    {
        endValue = end;
        distance = endValue - (*target);
        Finished = finished;
        Begin(_duration);
    }

    virtual void Update(float dt)
    {
        if (IsFinished())
        {
            (*target) = endValue;
            if (Finished)
            {
                QVariantMap args;
                args["Interpolator*"] = QVariant::fromValue(this);
                Finished->Invoke(args);
                Finished=0;
            }
            return;
        }
        if (IsStarted())
            (*target) += (dt/Duration)*distance;
    }

    T& getEndValue() { return endValue; }

private:
    T*      target;
    T       endValue;
    T       distance;
    Delegate *Finished;
};

#include <QVector2D>
#include <QVector3D>
typedef Interpolator<float>     FloatInterpolator;
Q_DECLARE_METATYPE(FloatInterpolator*)

typedef Interpolator<QVector2D> QV2Interpolator;
Q_DECLARE_METATYPE(QV2Interpolator*)

typedef Interpolator<QVector3D> QV3Interpolator;
Q_DECLARE_METATYPE(QV3Interpolator*)

#endif // _INTERPOLATOR_H
