#ifndef SPRITESFROMTEXTURE_H
#define SPRITESFROMTEXTURE_H
#include "ExampleBase.h"
#include "SpriteMap.h"

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
    SpriteMap     atlas;
    Sprite*       ring;
    Sprite*       star;
};

#endif // SPRITESFROMTEXTURE_H
