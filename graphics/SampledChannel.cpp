#include "SampledChannel.h"

SampledChannel::SampledChannel(FloatArray points, float duration)
    : Duration(duration)
    , Points(points)
{
    numSamples = Points.size();
    stepDuration = Duration/float(numSamples-1);
}

float	SampledChannel::GetPoint(float t)
{
    if (numSamples<2)	return -9999;

    int index;
    float ratio = calcIndexRatio(t, index);
    if (index>=numSamples-1)
        return Points[numSamples-1];

    return  Points[index+1]*ratio + Points[index]*(1.f-ratio);
}

float SampledChannel::calcIndexRatio(float t, int &index)
{
    index = int(t/stepDuration);
    return t/stepDuration - float(index);
}
