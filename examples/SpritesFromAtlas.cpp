#include "SpritesFromAtlas.h"
#include "Graphics.h"
#include <math.h>

SpritesFromAtlas::SpritesFromAtlas()
    : atlas(50, ":/textures/textures.atlas")
    , t(0)
{
    screenWidth = Graphics::Screen.Width();
    screenHeight= Graphics::Screen.Height();

    ring = atlas.CreateSprite("slot.png");

    spark = atlas.CreateSprite("energy1.png");
    sparkAnim.Init(.8f, 1, 6, 6, &spark->getUVRect() );

    runner = atlas.CreateSprite("Runner.png");
    runnerAnim.Init(.35f, 4, 1, 4, &runner->getUVRect() );

    Resize(screenWidth, screenHeight);
}

SpritesFromAtlas::~SpritesFromAtlas()
{
}

void SpritesFromAtlas::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;

    atlas.Render();
}

void SpritesFromAtlas::Update(float dt)
{
    t+=dt;

    ring->setPos( screenPos( sin(t), 0.7f) );
    spark->setPos( screenPos(0.f, -0.6f) );
    runner->setPos(screenPos(-sin(t), 0.0f) );

    sparkAnim.Update(dt);
    spark->setUVRect( sparkAnim.GetCellUVs() );
    runnerAnim.Update(dt);
    runner->setUVRect( runnerAnim.GetCellUVs() );

    atlas.Update();
}

void SpritesFromAtlas::Resize(float w, float h)
{
    Graphics::rasterShader->UpdateViewport( Graphics::Screen );

    screenWidth = w;
    screenHeight = h;
    ring->setSize( rectSize(0.15f) );
    spark->setSize( rectSize(0.3f) );
    runner->setSize( rectSize(0.3f, 0.6f) );
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
