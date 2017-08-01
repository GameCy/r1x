#ifndef EVENTARGS_H
#define EVENTARGS_H

#include <QString>
#include "SmartPtr.h"

class EventArgs
{
public:
    EventArgs()
        :Data(0), ReturnValue(0), destroyData(false) {}

    EventArgs(QString eventName, void* data, bool destroyData=true)
        : EventName(eventName), Data(data), destroyData(destroyData)
    {
    }

    ~EventArgs()
    {
        if (Data && destroyData)
            delete Data;
    }

    QString EventName;
    void*	Data;
    bool    destroyData;
    void*	ReturnValue;
};

typedef SmartPtr<EventArgs> EventArgsPtr;

#endif // EVENTARGS_H
