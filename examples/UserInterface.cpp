#include "UserInterface.h"
#include "Graphics.h"
#include "UI.h"

UserInterface::UserInterface()
{
    uiFactory = new UIFactory(":/textures/textures.atlas", 50, "Pipe48");

    buttonPrev = uiFactory->CreateButton("Previous");
    buttonNext = uiFactory->CreateButton("Next");
}

void UserInterface::Render()
{
    uiFactory->Render();
}

void UserInterface::Update(float dt)
{
    uiFactory->Update();
}

void UserInterface::Resize(float w, float h)
{
    buttonPrev->SetPos( Graphics::Screen.Normalized(0.05f, 0.0f) );
    buttonNext->SetPos( Graphics::Screen.Normalized(0.55f, 0.0f) );

    buttonPrev->SetSize( Graphics::Screen.Normalized(0.4f, 0.2f) );
    buttonNext->SetSize( Graphics::Screen.Normalized(0.4f, 0.2f) );
}
