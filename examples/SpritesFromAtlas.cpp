#include "SpritesFromAtlas.h"
#include "Graphics.h"
#include <math.h>

SpritesFromAtlas::SpritesFromAtlas()
    : atlas(50, ":/textures/textures.atlas")
    , ring( atlas.CreateSprite("slot.png") )
    , runner( atlas.CreateSprite("Runner.png") )
    , runnerAnimator(runner, &runnerFrames)
    , spark( atlas.CreateSprite("energy1.png") )
    , sparkAnimator(spark, &sparkFrames)
{
    screenWidth = Graphics::Screen.Width();
    screenHeight= Graphics::Screen.Height();

    sparkFrames.InitCellsFromGrid(1, 6, 6, &spark->getUVRect());
    sparkAnimator.Repeat(15);// loop 15 times
    sparkAnimator.Begin(1.2f);

    runnerFrames.InitCellsFromGrid( 4, 1, 4, &runner->getUVRect() );
    runnerAnimator.Begin(0.7f);
    runnerAnimator.Repeat();

    Resize( Graphics::Screen );
    Begin();
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
    ring->setPos( screenPos( -0.1f -0.8f*sin(Time+1.3f), 0.7f) );
    runner->setPos(screenPos(-0.15f -0.7f*sin(Time), 0.1f) );
    spark->setPos( screenPos(0.f, -0.4f) );

    ring->setRotationAngle( float(-12.f*Time) );
    spark->setRotationAngle( 2.f*Time );
    atlas.Update();
}

void SpritesFromAtlas::Resize(ViewPort &screen)
{
    Graphics::rasterShader->UpdateViewport( screen );

    screenWidth = screen.Width();
    screenHeight = screen.Height();
    ring->setSize( rectSize(0.13f, 0.18f) );
    runner->setSize( rectSize(0.3f, 0.5f) );
    spark->setSize( rectSize( 0.3f) );
    spark->setRotationCenter( spark->getSize()*0.5f );

    // set rotation center for ring to be outside of ring
    ring->setRotationCenter( .5f*ring->getSize() );
}

QVector2D SpritesFromAtlas::rectSize(float size)
{
    float W = screenWidth*size;
    float H = W * Graphics::DPI.VIEWPORT_ASPECT_RATIO;
    return QVector2D(W,H);
}

QVector2D SpritesFromAtlas::rectSize(float sx, float sy)
{
    float W = sx*screenWidth;
    float H = sy*screenHeight * Graphics::DPI.VIEWPORT_ASPECT_RATIO;
    return QVector2D(W,H);
}

QVector2D SpritesFromAtlas::screenPos(float x, float y)
{
    float px = screenWidth*( 1.f + x)/2.f;
    float py = screenHeight*(1.f + y)/2.f;
    return QVector2D(px,py);
}
