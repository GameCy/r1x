#include "SpritesFromAtlas.h"
#include "Graphics.h"
#include <math.h>

SpritesFromAtlas::SpritesFromAtlas()
    : atlas(50, ":/textures/textures.atlas")
    , t(0)
{
    screenWidth = Graphics::Screen.Width();
    screenHeight= Graphics::Screen.Height();

    ring = atlas.CreateSprite("slot.png", 0,0);
    ring->setSize( rectSize(0.2f) );

    star = atlas.CreateSprite("star_particle.png", 0,0);
    star->setSize( rectSize(0.1f) );

    spark = atlas.CreateSprite("energy1.png", 0,0);
    spark->setSize( rectSize(0.3f) );
    sparkAnim.Init(.8f, 1, 6, 6, &spark->getUVRect() );

    runner = atlas.CreateSprite("Runner.png", 0,0);
    runner->setSize( rectSize(0.3f, 0.6f) );
    runnerAnim.Init(.35f, 4, 1, 4, &runner->getUVRect() );

    atlas.GetMaterial()->Blending = true;
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
    t+=dt;
    ring->setPos( screenPos(0.5f*sin(t*2.4), 0.5f*cos(t)) );
    star->setPos( screenPos(0.5f*cos(t*1.6), 0.5f*sin(t)) );
    //spark->setPos( screenPos(0.4f*cos(t*1.2), 0.4f*sin(t*2.f)) );
    spark->setPos( screenPos(0.f, -0.6f) );
    runner->setPos(screenPos(-0.2f, 0.0f) );

    sparkAnim.Update(dt);
    spark->setUVRect( sparkAnim.GetCellUVs() );
    runnerAnim.Update(dt);
    runner->setUVRect( runnerAnim.GetCellUVs() );

    atlas.Update();
}

QVector2D SpritesFromAtlas::rectSize(float size)
{
    float W = screenWidth*size;
    float H = W * Graphics::DPI.ASPECT_RATIO;
    return QVector2D(W,H);
}

QVector2D SpritesFromAtlas::rectSize(float sx, float sy)
{
    float W = sx*screenWidth;
    float H = sy*screenHeight * Graphics::DPI.ASPECT_RATIO;
    return QVector2D(W,H);
}

QVector2D SpritesFromAtlas::screenPos(float x, float y)
{
    float px = screenWidth*( 1.f + x)/2.f;
    float py = screenHeight*(1.f + y)/2.f;
    return QVector2D(px,py);
}
