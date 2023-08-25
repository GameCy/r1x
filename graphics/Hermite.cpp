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

// ----------------------------------------------------------------------

Hermite::Hermite(float stiffness)
    : Stiffness(stiffness)
{
}

// numSamples can be zero and no samples will be computed
void	Hermite::Init(int numpoints, float* xyz=0)
{
	ControlPoints.clear();

	while(numpoints)
	{
        ControlPoints.push_back( QVector3D( xyz[0], xyz[1], xyz[2]) );
		xyz+=3;
		numpoints--;
	}
    InitTangets();
}

void Hermite::InitTangets()
{
    ComputeTangents(ControlPoints, Tangents, Stiffness);
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
    if (sampled->TotalLength==0.f)
        return; // distance between points must not be zero
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
}

// do the interpolation, t= 0 .. (n-1)
QVector3D	Hermite::Interpolate(float t)
{
    if ( ControlPoints.size()<3 || Tangents.size()<2 )	return QVector3D(0,0,0);

	int segment = (int) t;
    float weight = t- (float)segment;

    if ( std::size_t(segment+2) > ControlPoints.size())	return QVector3D(0,0,0);	// numseg=nump-1; need to have segment<=numseg;

    return HermiteInterpolate( ControlPoints[segment], ControlPoints[segment+1]
                            , Tangents[segment], Tangents[segment+1], weight );
}

