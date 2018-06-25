#include "SampledChannel.h"

SampledChannel::SampledChannel(FloatArray points, float duration)
    : Duration(duration)
    , Points(points)
{
    numSamples = Points.size();
}

float	SampledChannel::GetPoint(float t)
{
    if (numSamples<1)	return -9999;

    int index;
    float ratio = calcIndexRatio(t, index);
    if (index>=numSamples-1)
        return Points[numSamples-1];

    return ( Points[index]*ratio + Points[index+1]*(1.0f-ratio) );
}

float SampledChannel::calcIndexRatio(float t, int &index)
{
    float ratio = t/Duration;
    index = int(ratio*Points.size());

    return ratio;
}
