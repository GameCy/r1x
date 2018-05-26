#include "Hermite.h"
//#include <memory.h>
#include <math.h>

// (c) Soteris Stylianou, feb 2003, revised 2014, 2018
//
// there is a nice explanation of hermite curves here:
// http://www.cubic.org/~submissive/sourcerer/hermite.htm

QVector3D HermiteInterpolate(QVector3D &point1, QVector3D &point2, QVector3D &tangentP1, QVector3D &tangentP2, float weight)
{
    float w2,w3,h1,h2,h3,h4;
    w2 = weight*weight;
    w3 = w2*weight;
    h1 =  2*w3 - 3*w2 + 1;
    h2 = -2*w3 + 3*w2;			// basis function 2
    h3 =  w3 - 2*w2 + weight;	// basis function 3
    h4 =  w3 - w2;				// basis function 4

    return (  point1*h1 + point2*h2 + tangentP1*h3 + tangentP2*h4 );
}

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

// ----------------------------------------------------------------------

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

    float x = t/TotalTime*TotalLength;
    int idx1 = (int) (x/StepLength);
    int idx2 = idx1+1;
    if (idx1>=numSamples-1)
        return Points[numSamples-1];

    float ratio =	( (float)idx2*StepLength - x) /
                    ( (float)idx2*StepLength - (float)idx1*StepLength);

    return ( Points[idx1]*ratio + Points[idx2]*(1.0f-ratio) );
}

QVector3D SampledCurve::GetTangent(float t)
{
    int numSamples = Tangents.size();
    if (numSamples<1)	return QVector3D(0,0,0);

    float x = t/TotalTime*TotalLength;
    int idx1 = (int) (x/StepLength);
    int idx2 = idx1+1;
    if (idx1>=numSamples-1)
        return Tangents[numSamples-1];

    float ratio =	( (float)idx2*StepLength - x) /
                    ( (float)idx2*StepLength - (float)idx1*StepLength);

    return ( Tangents[idx1]*ratio + Tangents[idx2]*(1.0f-ratio) );
}

void SampledCurve::MakeTangents(float stiffness)
{
    ComputeTangents(Points, Tangents, stiffness);
}

// ----------------------------------------------------------------------

Hermite::Hermite(float stiffness)
    : Stiffness(stiffness)
{
}

// numSamples can be zero and no samples will be computed
void	Hermite::Init(float duration, int numSamples, int numpoints, float* xyz=0)
{
	ControlPoints.clear();

	while(numpoints)
	{
        ControlPoints.push_back( QVector3D( xyz[0], xyz[1], xyz[2]) );
		xyz+=3;
		numpoints--;
	}

    ComputeTangents(ControlPoints, Tangents, Stiffness);
//    ComputeSamples(numSamples);
//	ComputeTangents(SamplePoints, SampleTangents);
}


float	Hermite::CalculateTotalLength(float step)
{
	if (ControlPoints.size()<1)	return -1.0f;
	if (Tangents.size()==0)
        ComputeTangents(ControlPoints, Tangents, Stiffness);
	
	// sample curve length
	float total_len=0;
    QVector3D sample1, sample2;
	float numPoints = (float) ControlPoints.size();
	
	sample1 = Interpolate( 0.0);

	float t;
	for(t=step; t<(numPoints-1.0f); t+=step)
	{
		sample2 = sample1;
		sample1 = Interpolate(t);

        total_len += (sample1-sample2).length();
	}
	return total_len;
}

void	Hermite::MakeSampledCurve(int numSamples, SampledCurve* sampled)
{
    if (ControlPoints.size()<1)
        return;

    sampled->Points.clear();

	// sample curve length
    float travel=0;
    QVector3D sample1, sample2;
	float numPoints = (float) ControlPoints.size();
	float step = 0.1f*((float)(numPoints-1.0f)/(float)numSamples);
	
    sampled->TotalLength = CalculateTotalLength(step);
    sampled->StepLength = sampled->TotalLength/float(numSamples-1);

	// sample equidistant points
    travel = 0;
	sample1 = Interpolate( 0.0);
    sampled->Points.push_back( sample1);
	int count=1;
	for(float t=step; t<=(numPoints-1.0f); t+=step)
	{
		sample2 = sample1;
		sample1 = Interpolate( t);
        travel += (sample1-sample2).length();
        if (travel>=sampled->StepLength)
		{
			if (count>=(numSamples-1))	break;
            travel -= sampled->StepLength;
            sampled->Points.push_back(sample1);
			++count;
		}
	}
	if (count<numSamples) // last point
        sampled->Points.push_back( ControlPoints.back() );

    ComputeTangents(sampled->Points, sampled->Tangents, Stiffness);
}

// do the interpolation, t= 0 .. (n-1)
QVector3D	Hermite::Interpolate(float t)
{
    if ( ControlPoints.size()<3 || Tangents.size()<2 )	return QVector3D(0,0,0);

	int segment = (int) t;
	float s = t- (float)segment;

    if ( (segment+2) > ControlPoints.size())	return QVector3D(0,0,0);	// numseg=nump-1; need to have segment<=numseg;

    return HermiteInterpolate( ControlPoints[segment], ControlPoints[segment+1], Tangents[segment], Tangents[segment+1], s );
}

