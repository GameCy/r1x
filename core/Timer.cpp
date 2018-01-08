#include "Timer.h"


Timer::Timer()
    : Time(0)
    , Ellapsed(0)
{}

Timer::~Timer()
{}

// resets the starting time
void Timer::ResetTimer()
{
    clock_gettime(CLOCK_MONOTONIC, &first);
    old = first;
    Time = Ellapsed = 0;
}

// updates Time and Ellapsed
// measures in seconds starting from 0 when the ResetTimer func is called
void Timer::UpdateTimer()
{
    struct timespec current;
    clock_gettime(CLOCK_MONOTONIC, &current);

    Ellapsed	= float(current.tv_sec - old.tv_sec) + float(current.tv_nsec - old.tv_nsec)/1000000000.f;
    Time		= float(current.tv_sec - first.tv_sec) + float(current.tv_nsec - first.tv_nsec)/1000000000.f;
    old = current;
}

float   Timer::GetFrameTime()
{
    if (Ellapsed>0.3f)
        return 0.3f;
    return Ellapsed;
}
