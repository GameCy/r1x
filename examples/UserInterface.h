#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "ExampleBase.h"
#include "UIFactory.h"
#include "FrameRate.h"

class UserInterface : public ExampleBase
{
public:
    UserInterface();

    // Temporal interface
    void Update(float dt);
    // ExampleBase interface
    void Render();
    void Resize(float w, float h);

    ButtonPtr buttonPrev;
    ButtonPtr buttonNext;

private:
    UIFactory*  uiFactory;

    TextLabelPtr    fpsLabel;
    FrameRate       fpsCounter;

};

#endif // USERINTERFACE_H
