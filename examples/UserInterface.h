#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "ExampleBase.h"
#include "UIFactory.h"
#include "ViewPort.h"
#include "FrameRate.h"

class UserInterface : public ExampleBase
{
public:
    UserInterface();
    ~UserInterface();

    // Temporal interface
    void Update(float dt);
    // ExampleBase interface
    void Render();
    void Resize(ViewPort &screen);

    Button* buttonPrev;
    Button* buttonNext;

private:
    UIFactory*  uiFactory;

    TextLabel*  fpsLabel;
    FrameRate   fpsCounter;

};

#endif // USERINTERFACE_H
