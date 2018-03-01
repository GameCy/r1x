#ifndef EXAMPLEBASE_H
#define EXAMPLEBASE_H


class ExampleBase
{
public:
    virtual ~ExampleBase() {}

    virtual void Render()=0;
    virtual void Update(float dt)=0;
    virtual void Resize(float w, float h)=0;
};

#endif // EXAMPLEBASE_H
