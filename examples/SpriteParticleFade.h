#ifndef SPRITEPARTICLEFADE_H
#define SPRITEPARTICLEFADE_H
#include "ExampleBase.h"
#include "SpriteMap.h"
#include "BlinkFloat.h"

class SpriteParticleFade : public ExampleBase
{
public:
    SpriteParticleFade();
    virtual ~SpriteParticleFade();

    // Temporal interface
    void Update(float dt);
    // ExampleBase interface
    void Render();
    void Resize(ViewPort &screen);

private:
    SpriteMap   atlas;
    Sprite*     star[50];
    float       starTime[50];

    BlinkFloat  trigonometricParameter;

    QVector2D   rectSize(float size);
    QVector2D   rectSize(float sx, float sy);
    QVector2D   screenPos(float x, float y);
    float       screenWidth;
    float       screenHeight;
};

#endif // SPRITEPARTICLEFADE_H
