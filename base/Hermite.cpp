#include "Hermite.h"
//#include <memory.h>
#include <math.h>


// (c) Soteris Stylianou, feb 2003, revised 2014
//
// there is a nice explanation of hermite curves here:
// http://www.cubic.org/~submissive/sourcerer/hermite.htm

Hermite::Hermite()
{
	m_stiffness = 1.0f;
	m_TotalCurveLength=0;
}

Hermite::~Hermite()
{
}

// numSamples can be zero and no samples will be computed
void	Hermite::init(float duration, int numSamples, int numpoints, float* xyz=0)
{
	m_TotalTime = duration;
	ControlPoints.clear();

	while(numpoints)
	{
        ControlPoints.push_back( QVector3D( xyz[0], xyz[1], xyz[2]) );
		xyz+=3;
		numpoints--;
	}

	ComputeTangents(ControlPoints, Tangents);
	ComputeSamples(numSamples);
	ComputeTangents(SamplePoints, SampleTangents);
}

// numSamples can be zero and no samples will be computed
void	Hermite::initSamplesFromControlPoints(float duration, int numSamples)
{
	m_TotalTime = duration;

	ComputeTangents(ControlPoints, Tangents);
	ComputeSamples(numSamples);
	ComputeTangents(SamplePoints, SampleTangents);
}

// precompute tangents
void	Hermite::ComputeTangents(PointArray points, PointArray& tangents)
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
        tan *= m_stiffness;
		tangents.push_back(tan);
	}
	// last tangent is the same 
	tangents.push_back(tan);
}


float	Hermite::CalculateTotalLength(float step)
{
	if (ControlPoints.size()<1)	return -1.0f;
	if (Tangents.size()==0)
		ComputeTangents(ControlPoints, Tangents);
	
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

// now build correct time based precomputed positions on curve
void	Hermite::ComputeSamples(int numSamples)
{
	if (ControlPoints.size()<1)	return;

	SamplePoints.clear();

	// sample curve length
	float total_len=0;
    QVector3D sample1, sample2;
	float numPoints = (float) ControlPoints.size();
	float step = 0.1f*((float)(numPoints-1.0f)/(float)numSamples);
	
	m_TotalCurveLength = CalculateTotalLength(step);

	// sample equidistant points
	//numSamples = SamplePoints.size();
	float steplength = m_TotalCurveLength/float(numSamples-1);
	total_len = 0;
	sample1 = Interpolate( 0.0);
	SamplePoints.push_back( sample1);
	int count=1;
	for(float t=step; t<=(numPoints-1.0f); t+=step)
	{
		sample2 = sample1;
		sample1 = Interpolate( t);
        total_len += (sample1-sample2).length();
		if (total_len>=steplength)
		{
			if (count>=(numSamples-1))	break;
			total_len-=steplength;
			SamplePoints.push_back(sample1);
			++count;
		}
	}
	if (count<numSamples) // last point
		SamplePoints.push_back( ControlPoints.back() );
}

// actually calculate point now, dont use sampled points
QVector3D	Hermite::CalcPoint(float w)
{
	return Interpolate( w*float(ControlPoints.size()) );
}

// do the interpolation, t= 0 .. (n-1)
QVector3D	Hermite::Interpolate(float t)
{
    if ( ControlPoints.size()<3 || Tangents.size()<2 )	return QVector3D(0,0,0);

	int segment = (int) t;
	float s = t- (float)segment;

    if ( (segment+2) > ControlPoints.size())	return QVector3D(0,0,0);	// numseg=nump-1; need to have segment<=numseg;

	return RawCurveCalc(  ControlPoints[segment], ControlPoints[segment+1], Tangents[segment], Tangents[segment+1], s );
}

QVector3D Hermite::RawCurveCalc(QVector3D &point1, QVector3D &point2, QVector3D &tangentP1, QVector3D &tangentP2, float weight)
{
	float w2,w3,h1,h2,h3,h4;
	w2 = weight*weight;
	w3 = w2*weight;
	h1 =  2*w3 - 3*w2 + 1;
	h2 = -2*w3 + 3*w2;			// calculate basis function 2
	h3 =  w3 - 2*w2 + weight;	// calculate basis function 3
	h4 =  w3 - w2;				// calculate basis function 4

	return (  point1*h1 + point2*h2 + tangentP1*h3 + tangentP2*h4 );
}

// get point from previously computed samples, time-lenth corrected - beware
QVector3D	Hermite::GetPoint(float t)
{
    if (SamplePoints.size()<1)	return QVector3D(0,0,0);

	int numSamples = SamplePoints.size();
	float steplen = m_TotalCurveLength/(float(numSamples)-1.0f);
	float x = t/m_TotalTime*m_TotalCurveLength;
	int idx1 = (int) (x/steplen);
	int idx2 = idx1+1;
	if (idx1>=numSamples-1)
		return SamplePoints[numSamples-1];

	float ratio =	( (float)idx2*steplen - x) /
					( (float)idx2*steplen - (float)idx1*steplen);
	float inverseratio = 1.0f-ratio;
	
	return (SamplePoints[idx1]*ratio + SamplePoints[idx2]*inverseratio);
}

