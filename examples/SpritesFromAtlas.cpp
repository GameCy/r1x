#include "SpritesFromAtlas.h"
#include "Graphics.h"

SpritesFromAtlas::SpritesFromAtlas()
    : atlas(50, ":/textures/atlas1.atlas")
{
    float W = Graphics::Screen.Width()/10;
    float H = W * Graphics::DPI.ASPECT_RATIO;
    ring = atlas.CreateSprite("slot.png", W, H );
    star = atlas.CreateSprite("star_particle.png", W, H);

    ring->setPos( QVector2D( W*3, H*5) );
    star->setPos( QVector2D(W*5, H*2) );
}

SpritesFromAtlas::~SpritesFromAtlas()
{
}

void SpritesFromAtlas::Render()
{
    Graphics::phongShader->RasterMode( Graphics::Screen );
    atlas.Render();
}

void SpritesFromAtlas::Update(float dt)
{
    atlas.Update();
}
