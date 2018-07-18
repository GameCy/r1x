#ifndef SPRITESFROMTEXTURE_H
#define SPRITESFROMTEXTURE_H
#include "ExampleBase.h"
#include "SpriteMap.h"
#include "UVAnimator.h"

class SpritesFromAtlas : public ExampleBase
{
public:
    SpritesFromAtlas();
    virtual ~SpritesFromAtlas();

    // Temporal interface
    void Update(float dt);
    // ExampleBase interface
    void Render();
    void Resize(ViewPort &screen);

private:
    SpriteMap   atlas;
    Sprite      *ring;

    Sprite      *spark;
    UVRectArray sparkFrames;
    UVAnimator sparkAnimator;

    Sprite      *runner;
    UVRectArray runnerFrames;
    UVAnimator runnerAnimator;

    QVector2D   rectSize(float size);
    QVector2D   rectSize(float sx, float sy);
    QVector2D   screenPos(float x, float y);
    float       screenWidth;
    float       screenHeight;

};

#endif // SPRITESFROMTEXTURE_H
