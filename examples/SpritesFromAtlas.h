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

    // ExampleBase interface
public:
    virtual void Render();
    virtual void Update(float dt);
    virtual void Resize(float w, float h);

private:
    SpriteMap   atlas;
    Sprite*     ring;

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
