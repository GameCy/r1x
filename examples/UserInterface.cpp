#include "UserInterface.h"
#include "Graphics.h"
#include "UI.h"

UserInterface::UserInterface()
    : fpsCounter(1.0)
{
    uiFactory = new UIFactory(":/textures/textures.atlas", 50, "Pipe48");

    fpsLabel = uiFactory->CreateLabel("FPS");
    buttonPrev = uiFactory->CreateButton("Previous");
    buttonNext = uiFactory->CreateButton("Next");
}

void UserInterface::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;
    uiFactory->Render();
}

void UserInterface::Update(float dt)
{
    fpsCounter.AddHit(dt);
    fpsLabel->SetText( QString::asprintf("FPS: %.1f", fpsCounter.Get()) );
    uiFactory->Update();
}

void UserInterface::Resize(float w, float h)
{
    Graphics::rasterShader->UpdateViewport( Graphics::Screen );

    float textScale = Graphics::Screen.Width()/1000.f;
    fpsLabel->setScale(textScale);
    fpsLabel->SetPos( Graphics::Screen.Normalized(0.05f, 1.f - 0.15f*textScale) );

    buttonPrev->SetPos( Graphics::Screen.Normalized(0.05f, 0.0f) );
    buttonNext->SetPos( Graphics::Screen.Normalized(0.55f, 0.0f) );

    buttonPrev->SetSize( Graphics::Screen.Normalized(0.4f, 0.2f) );
    buttonNext->SetSize( Graphics::Screen.Normalized(0.4f, 0.2f) );
}
