#include "Randomizer.h"
#include <math.h>

Randomizer::Randomizer()
{
    m_w = 521288629;
    m_z = 362436069;
}

Randomizer::Randomizer(unsigned int u)
{
    m_w = u;
    m_z = 362436069;
}

Randomizer::Randomizer(unsigned int u, unsigned int v)
{
    m_w = u;
    m_z = v;
}

void Randomizer::ReSeed(unsigned int u)
{
    m_w = u;
    m_z = 362436069;
}

// Produce a uniform random sample from the open interval (0, 1).
// The method will not return either end point.
double Randomizer::GetUniform()
{
    unsigned int u = GetUint();
    // The magic number below is 1/(2^32 + 2).
    // The result is strictly between 0 and 1.
    return (u + 1.0) * 2.328306435454494e-10;
}

// Get normal (Gaussian) random sample with mean 0 and standard deviation 1
double Randomizer::GetNormal()
{
    // Use Box-Muller algorithm
    double u1 = GetUniform();
    double u2 = GetUniform();
    double r = sqrt( -2.0*log(u1) );
    double theta = 2.0*PI*u2;
    return r*sin(theta);
}

// Get normal (Gaussian) random sample with specified mean and standard deviation
double Randomizer::GetNormal(double mean, double standardDeviation)
{
    if (standardDeviation <= 0.0)
        standardDeviation = -standardDeviation;
    return mean + standardDeviation*GetNormal();
}

// Get exponential random sample with mean 1
double Randomizer::GetExponential()
{
    return -log( GetUniform() );
}

float Randomizer::GetFloat(float min, float max)
{
    return min + (max-min)*float(GetUint()%10000)/10000.0f;
}

float Randomizer::Get360f()
{
    return 360.0f*float(GetUint()%10000)/10000.0f;
}

bool Randomizer::GetBool()
{
    return (GetUint()%2)==1;
}

// It uses George Marsaglia's MWC algorithm to produce an unsigned integer.
// See http://www.bobwheeler.com/statistics/Password/MarsagliaPost.txt
unsigned int Randomizer::GetUint()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}

QVector3D Randomizer::RandPos(float radius)
{
    return QVector3D(radius*0.5 - GetFloat(0, radius), 0, radius*0.5 - GetFloat(0, radius));
}
