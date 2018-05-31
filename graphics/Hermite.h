#ifndef _HERMITE_H_
#define _HERMITE_H_
#include "SampledCurve.h"

QVector3D HermiteInterpolate(QVector3D &point1, QVector3D &point2, QVector3D &tangentP1, QVector3D &tangentP2, float weight);

class Hermite
{
public:
    Hermite(float stiffness=1.f);

    void Init(int numpoints, float* xyz);
    void InitTangets();

    QVector3D		Interpolate(float t); // t = 0.0 to numpoints-1

    float	CalculateTotalLength(float step);
    // samples are equidistant, thus speed is constant over the curve
    void	MakeSampledCurve(int numSamples, SampledCurve* sampled);

	PointArray	ControlPoints; // control points
    PointArray	Tangents;
    float	Stiffness;
};

#endif
