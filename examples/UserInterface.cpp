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

void UserInterface::Resize(ViewPort &screen)
{
    Graphics::rasterShader->UpdateViewport( screen );

    float textScale = screen.Width()/1000.f;
    fpsLabel->setScale(textScale);
    fpsLabel->SetPos( screen.Normalized(0.05f, 1.f - 0.15f*textScale) );

    buttonPrev->SetPos( screen.Normalized(0.05f, 0.0f) );
    buttonNext->SetPos( screen.Normalized(0.55f, 0.0f) );

    buttonPrev->SetSize( screen.Normalized(0.4f, 0.2f) );
    buttonNext->SetSize( screen.Normalized(0.4f, 0.2f) );
}
