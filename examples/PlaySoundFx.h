#ifndef PLAYSOUNDFX_H
#define PLAYSOUNDFX_H
#include "ExampleBase.h"
#include "Graphics.h"
#include "UIFactory.h"
#include "AudioManager.h"

class PlaySoundFx;

/*
class UIHandlers : public QObject
{
public:
    UIHandlers(PlaySoundFx* parent);

private slots:
    void playSound1ButtonClicked(InputArea* sender, QVector2D mousePos);
    void playSound2ButtonClicked(InputArea* sender, QVector2D mousePos);
    void loopingButtonClicked(InputArea* sender, QVector2D mousePos);

private:
    PlaySoundFx* parent
};
*/

class PlaySoundFx : public ExampleBase, public QObject
{
public:
    PlaySoundFx();
    virtual ~PlaySoundFx();

    // Temporal interface
    void Update(float dt);
    // ExampleBase interface
    void Render();
    void Resize(ViewPort &screen);

private slots:
    void playSound1ButtonClicked(InputArea* sender, QVector2D mousePos);
    void playSound2ButtonClicked(InputArea* sender, QVector2D mousePos);
    void loopingButtonClicked(InputArea* sender, QVector2D mousePos);

private:
    AudioManager audioMan;
    AudioSample*  sample1;
    AudioSample*  sample2;
    bool         loop;

    UIFactory*  uiFactory;
    Button*     buttonPlaySound1;
    Button*     buttonPlaySound2;
    Button*     buttonLooping;

    void applyLoopFlag(bool loopFlag);
};

#endif // PLAYSOUNDFX_H
