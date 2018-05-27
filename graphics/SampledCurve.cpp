#include "SampledCurve.h"


void ComputeTangents(PointArray points, PointArray& tangents, float stiffness)
{
    if (points.size()<1)	return;

    tangents.clear();

    QVector3D p1, p2, tan;
    int numPoints = points.size();
    for(int i = 0; i<numPoints; ++i)
    {
        if (i>0)	p1 = points[i-1];
        else		p1 = points[i];

        if (i<(numPoints-1))	p2 = points[i+1];
        else					p2 = points[i];

        tan = p2 - p1;
        tan *= stiffness;
        tangents.push_back(tan);
    }
    // last tangent is the same
    tangents.push_back(tan);
}

SampledCurve::SampledCurve(float duration)
    : TotalTime(duration)
    , TotalLength(0)
    , StepLength(0)
{
}

QVector3D	SampledCurve::GetPoint(float t)
{
    int numSamples = Points.size();
    if (numSamples<1)	return QVector3D(0,0,0);

    int index;
    float ratio = calcIndexRatio(t, index);
    if (index>=numSamples-1)
        return Points[numSamples-1];

    return ( Points[index]*ratio + Points[index+1]*(1.0f-ratio) );
}

QVector3D SampledCurve::GetTangent(float t)
{
    int numSamples = Tangents.size();
    if (numSamples<1)	return QVector3D(0,0,0);

    int index;
    float ratio = calcIndexRatio(t, index);
    if (index>=numSamples-1)
        return Tangents[numSamples-1];

    return ( Tangents[index]*ratio + Tangents[index+1]*(1.0f-ratio) );
}

float SampledCurve::calcIndexRatio(float t, int &index)
{
    float x = t/TotalTime*TotalLength;
    float f_index = x/StepLength;
    index = int(f_index);

    float minT = f_index*StepLength;
    float maxT = (f_index+1)*StepLength;
    return (maxT - x) / (maxT - minT);
}

void SampledCurve::MakeTangents(float stiffness)
{
    ComputeTangents(Points, Tangents, stiffness);
}
