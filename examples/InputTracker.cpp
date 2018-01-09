#include "InputTracker.h"

InputTracker* InputTracker::instance=0;

InputTracker& InputTracker::Instance()
{
    if (instance==0)    instance = new InputTracker;
    return (*instance);
}

InputTracker::InputTracker()
{ }

void InputTracker::feedTapBegin(QVector2D pos)
{
    emit TapBegin(pos);
}

void InputTracker::feedTapMove(QVector2D pos)
{
    emit TapMove(pos);
}

void InputTracker::feedTapEnd(QVector2D pos)
{
    emit TapEnd(pos);
}
