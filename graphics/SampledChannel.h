#ifndef SAMPLEDCHANNEL_H
#define SAMPLEDCHANNEL_H
#include <vector>
#include <QVector3D>

typedef std::vector<float>	FloatArray;

class SampledChannel
{
public:
    SampledChannel(FloatArray points, float duration);

    float GetPoint(float t);

    float	Duration;
    FloatArray	Points;
private:
    float calcIndexRatio(float t, int &index);
    int numSamples;
    float stepDuration;
};

#endif // SAMPLEDCHANNEL_H
