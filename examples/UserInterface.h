#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "ExampleBase.h"
#include "UIFactory.h"

class UserInterface : public ExampleBase
{
public:
    UserInterface();

    // ExampleBase interface
public:
    void Render();
    void Update(float dt);
    void Resize(float w, float h);

private:
    UIFactory*  uiFactory;

    ButtonPtr buttonPrev;
    ButtonPtr buttonNext;
};

#endif // USERINTERFACE_H
