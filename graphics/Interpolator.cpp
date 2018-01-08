/*
#include "Interpolator.h"

#include <QDebug>
void TestInterpolatorFloat()
{
    float value = 9.f;
    FloatInterpolator flit(&value);

    flit.Start(-3.4f, 2.f);
    while(!flit.IsFinished())
    {
        flit.Update(0.023f);
        qDebug() << value;
    }
}

void TestInterpolatorQV3()
{
    QVector3D value(8,-3,0);
    QV3Interpolator flit(&value);

    flit.Start(QVector3D(0, 4, -5), 2.f);
    while(!flit.IsFinished())
    {
        flit.Update(0.023f);
        qDebug() << value;
    }
}
*/
