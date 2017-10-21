#if !defined(_TIMER_H_INCLUDED_)
#define _TIMER_H_INCLUDED_
#include <time.h>

class Timer
{
public:
    Timer();
    virtual ~Timer();
	void    ResetTimer();
	void    UpdateTimer();
    float   GetFrameTime();

    float	Time;		// in sec since last call to ResetTimer
    float	Ellapsed;	// in sec since last call to UpdateTimer();
private:
    struct timespec first;
    struct timespec old;
};

#endif 
