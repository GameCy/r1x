#ifndef EXAMPLEBASE_H
#define EXAMPLEBASE_H
#include "Temporal.h"
#include "ViewPort.h"

class ExampleBase : public Temporal
{
public:
    ExampleBase()               { TemporalPool::Add(this); }
    virtual ~ExampleBase()      { }

    virtual void Render()=0;
    virtual void Resize(ViewPort &screen)=0;
};

#endif // EXAMPLEBASE_H
