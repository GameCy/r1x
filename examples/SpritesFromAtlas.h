#ifndef SPRITESFROMTEXTURE_H
#define SPRITESFROMTEXTURE_H
#include "ExampleBase.h"
#include "SpriteMap.h"
#include "UVAnim.h"

class SpritesFromAtlas : public ExampleBase
{
public:
    SpritesFromAtlas();
    ~SpritesFromAtlas();

    // ExampleBase interface
public:
    virtual void Render();
    virtual void Update(float dt);

private:
    SpriteMap   atlas;
    Sprite*     ring;
    Sprite*     star;

    Sprite*     spark;
    UVAnim      sparkAnim;

    Sprite*     runner;
    UVAnim      runnerAnim;

    QVector2D   rectSize(float size);
    QVector2D   rectSize(float sx, float sy);
    QVector2D   screenPos(float x, float y);
    float       screenWidth;
    float       screenHeight;
    float       t;
};

#endif // SPRITESFROMTEXTURE_H
