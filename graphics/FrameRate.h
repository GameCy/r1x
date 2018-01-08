#ifndef _FRAMERATE_H_
#define _FRAMERATE_H_

class FrameRate
{
public:
    FrameRate(float sampletime);

	void	AddHit(float dt);
	float	Get();

	int hitcount, halfcount;
	float duration, halfdur, maxhalf,maxdur;

};

#endif
