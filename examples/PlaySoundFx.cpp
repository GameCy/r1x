#include "PlaySoundFx.h"
#include <math.h>


PlaySoundFx::PlaySoundFx()
    : QObject()
    , loop(false)
{
    sample1 = new AudioSample(QApplication::focusWidget(), audioMan.Get(":/sounds/Powerup.wav"));
    sample2 = new AudioSample(QApplication::focusWidget(), audioMan.Get(":/sounds/going-down.wav"));

    uiFactory = new UIFactory(":/textures/textures.atlas", 50, "Pipe48");

    buttonPlaySound1 = uiFactory->CreateButton("play sound 1");
    buttonPlaySound2 = uiFactory->CreateButton("play sound 2");
    buttonLooping = uiFactory->CreateButton("looping text");

    Resize(Graphics::Screen);
    applyLoopFlag(loop);

    connect(buttonPlaySound1, &Button::Clicked, this, &PlaySoundFx::playSound1ButtonClicked);
    connect(buttonPlaySound2, &Button::Clicked, this, &PlaySoundFx::playSound2ButtonClicked);
    connect(buttonLooping, &Button::Clicked, this, &PlaySoundFx::loopingButtonClicked);
    Begin();
}

PlaySoundFx::~PlaySoundFx()
{
    sample1->Stop();
    sample1->deleteLater();
    sample2->Stop();
    sample2->deleteLater();
    //audioMan.ClearAll();

    buttonLooping->DeleteLater();
    buttonPlaySound1->DeleteLater();
    buttonPlaySound2->DeleteLater();
}

void PlaySoundFx::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;

    uiFactory->Render();
}

void PlaySoundFx::Update(float dt)
{
    audioMan.RegularCleanup();
}

void PlaySoundFx::Resize(ViewPort &screen)
{
    Graphics::rasterShader->UpdateViewport( screen );

    buttonPlaySound1->SetPos( screen.Normalized(0.2f, 0.7f) );
    buttonPlaySound2->SetPos( screen.Normalized(0.2f, 0.5f) );
    buttonLooping->SetPos( screen.Normalized(0.2f, 0.3f) );

    buttonPlaySound1->SetSize( screen.Normalized(0.6f, 0.2f) );
    buttonPlaySound2->SetSize( screen.Normalized(0.6f, 0.2f) );
    buttonLooping->SetSize( screen.Normalized(0.4f, 0.2f) );

    uiFactory->Update();
}

void PlaySoundFx::playSound1ButtonClicked(InputArea *sender, QVector2D mousePos)
{
    if (sample2->isPlaying())
        sample2->Stop();
    sample1->Start();
}

void PlaySoundFx::playSound2ButtonClicked(InputArea *sender, QVector2D mousePos)
{
    if (sample1->isPlaying())
        sample1->Stop();
    sample2->Start();
}

void PlaySoundFx::loopingButtonClicked(InputArea *sender, QVector2D mousePos)

{
    loop = !loop;
    applyLoopFlag(loop);
}

void PlaySoundFx::applyLoopFlag(bool loopFlag)
{
    sample1->Loop(loopFlag);
    sample2->Loop(loopFlag);
    buttonLooping->SetText( loopFlag ? "no loop" : "loop");
    uiFactory->Update();
}
