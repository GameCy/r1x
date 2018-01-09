#ifndef EXAMPLEBASE_H
#define EXAMPLEBASE_H


class ExampleBase
{
public:
    virtual void Render()=0;
    virtual void Update(float dt)=0;
};

#endif // EXAMPLEBASE_H
