#include "FrameRate.h"

FrameRate::FrameRate(float sampletime)
		
{
	hitcount=0; halfcount=0;
	duration=0;
	maxdur=sampletime;
	maxhalf=sampletime*2.0f;
	halfdur=maxhalf/2.0f;
}


void	FrameRate::AddHit(float dt)
{
	hitcount++;		duration+=dt;
	if (duration>maxhalf)
	{
		hitcount /= 2;
		duration /= 2.0f;
	}
}

float	FrameRate::Get()
{
	return float(hitcount)/duration;
}
