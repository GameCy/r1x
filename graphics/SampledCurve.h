#ifndef SAMPLEDCURVE_H
#define SAMPLEDCURVE_H
#include <vector>
#include <QVector3D>

typedef std::vector<QVector3D>	PointArray;

void	ComputeTangents(PointArray points, PointArray& tangents, float stiffness);

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

#endif // SAMPLEDCURVE_H
