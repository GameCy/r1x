#ifndef RANDOMIZER_H
#define RANDOMIZER_H
#include <QVector3D>

class Randomizer
{
public:
    // The random generator seed can be set three ways:
    // 1) specifying two non-zero unsigned integers
    // 2) specifying one non-zero unsigned integer and taking a default value for the second
    // 3) setting the seed from the system time
    Randomizer();
    Randomizer(unsigned int u);
    Randomizer(unsigned int u, unsigned int v);
    void ReSeed(unsigned int u);

    // Produce a uniform random sample from the open interval (0, 1).
    // The method will not return either end point.
    double GetUniform();
    // Get normal (Gaussian) random sample with mean 0 and standard deviation 1
    double GetNormal();

    // Get normal (Gaussian) random sample with specified mean and standard deviation
    double GetNormal(double mean, double standardDeviation);

    // Get exponential random sample with mean 1
    double GetExponential();

    float GetFloat(float min, float max);

    float Get360f();

    bool GetBool();

    unsigned int GetUint();

    QVector3D RandPos(float radius);

private:
    unsigned int m_w;
    unsigned int m_z;
    const double PI=3.141592;
};

extern Randomizer GlobalRandom;
#endif // RANDOMIZER_H
