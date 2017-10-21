#ifndef EVENTARGS_H
#define EVENTARGS_H
#include <string>

class EventArgs
{
public:
    EventArgs()
        :Data(0), ReturnValue(0) {}

    EventArgs(std::string typeName, void* data)
        : TypeName(typeName), Data(data)
    {
    }

    std::string TypeName;
    void*		Data;
    void*		ReturnValue;
};

#endif // EVENTARGS_H
