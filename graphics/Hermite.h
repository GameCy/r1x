#ifndef _HERMITE_H_
#define _HERMITE_H_
#include <vector>
#include <QVector3D>

typedef std::vector<QVector3D>	PointArray;

void	ComputeTangents(PointArray points, PointArray& tangents, float stiffness);

QVector3D HermiteInterpolate(QVector3D &point1, QVector3D &point2, QVector3D &tangentP1, QVector3D &tangentP2, float weight);

// ------------------------------------------

class SampledCurve
{
public:
    SampledCurve(float duration);

    QVector3D	GetPoint(float t);

    void        MakeTangents(float stiffness);
    QVector3D	GetTangent(float t);

    float	TotalTime;
    float	TotalLength;
    float   StepLength;
    PointArray	Points;
    PointArray	Tangents;
private:
    float calcIndexRatio(float t, int &index);
};

// ------------------------------------------

class Hermite
{
public:
    Hermite(float stiffness=1.f);

    void	Init(float duration, int numSamples, int numpoints, float* xyz);
    QVector3D		Interpolate(float t); // t = 0.0 to numpoints-1

    float	CalculateTotalLength(float step);
    // samples are equidistant, thus speed is constant over the curve
    void	MakeSampledCurve(int numSamples, SampledCurve* sampled);

	PointArray	ControlPoints; // control points
    PointArray	Tangents;
    float	Stiffness;
};

#endif
