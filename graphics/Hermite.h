#ifndef _HERMITE_H_
#define _HERMITE_H_
#include <vector>
#include <QVector3D>

typedef std::vector<QVector3D>	PointArray;

class Hermite
{
public:
	Hermite();
	virtual ~Hermite();

	void	SetPathDuration(float t)	{ m_TotalTime = t; }
	void	SetStiffness(float s)		{ m_stiffness = s; }

	// initialize and precompute samples
	// samples are equidistant, thus speed is constant over the curve
	void	init(float duration, int numSamples, int numpoints, float* xyz);
	float	CalculateTotalLength(float step);
	void	initSamplesFromControlPoints(float duration, int numSamples);

	// get point from samples calculated at initialization
    QVector3D		GetPoint(float t);
    QVector3D		GetTangent(float t);

	// calculate point, t = 0.0 to 1.0
    QVector3D		CalcPoint(float w);
	// calculate point, t = 0.0 to numpoints-1
    QVector3D		Interpolate(float t);
    static QVector3D RawCurveCalc(QVector3D &point1, QVector3D &point2, QVector3D &tangentP1, QVector3D &tangentP2, float weight);

	float	m_TotalTime;
	float	m_TotalCurveLength;

	PointArray	ControlPoints; // control points
	PointArray	SamplePoints;
	PointArray	SampleTangents;

	float	m_stiffness;

private:
	void	ComputeTangents(PointArray points, PointArray& tangents);
	void	ComputeSamples(int numSamples);

	PointArray	Tangents;
};

#endif

