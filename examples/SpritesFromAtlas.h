#ifndef SPRITESFROMTEXTURE_H
#define SPRITESFROMTEXTURE_H
#include "ExampleBase.h"
#include "SpriteMap.h"
#include "SpriteAnimator.h"

class SpritesFromAtlas : public ExampleBase
{
public:
    SpritesFromAtlas();
    virtual ~SpritesFromAtlas();

    // Temporal interface
    void Update(float dt);
    // ExampleBase interface
    void Render();
    void Resize(float w, float h);

private:
    SpriteMap   atlas;
    Sprite      *ring;

    Sprite      *spark;
    UVRectArray sparkFrames;
    SpriteAnimator sparkAnimator;

    Sprite      *runner;
    UVRectArray runnerFrames;
    SpriteAnimator runnerAnimator;

    QVector2D   rectSize(float size);
    QVector2D   rectSize(float sx, float sy);
    QVector2D   screenPos(float x, float y);
    float       screenWidth;
    float       screenHeight;

};

#endif // SPRITESFROMTEXTURE_H
