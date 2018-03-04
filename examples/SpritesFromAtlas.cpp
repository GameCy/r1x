#include "SpritesFromAtlas.h"
#include "Graphics.h"
#include <math.h>

SpritesFromAtlas::SpritesFromAtlas()
    : atlas(50, ":/textures/textures.atlas", true)
    , alphaAnim(10,255, 1.f)
    , t(0)
{
    screenWidth = Graphics::Screen.Width();
    screenHeight= Graphics::Screen.Height();

    ring = atlas.CreateSprite("slot.png");

    star = atlas.CreateSprite("star_particle.png");

    spark = atlas.CreateSprite("energy1.png");
    sparkAnim.Init(.8f, 1, 6, 6, &spark->getUVRect() );

    runner = atlas.CreateSprite("Runner.png");
    runnerAnim.Init(.35f, 4, 1, 4, &runner->getUVRect() );
    alphaAnim.Repeat(2000); // repeat blinking 2000 times

    atlas.GetMaterial()->Blending = true;

    Resize(screenWidth, screenHeight);
}

SpritesFromAtlas::~SpritesFromAtlas()
{
}

void SpritesFromAtlas::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;


    Graphics::rasterShader->UseColorPerVertex(true);
        atlas.GetMaterial()->Blending = true;
        atlas.Render();
    Graphics::rasterShader->UseColorPerVertex(false);
}

void SpritesFromAtlas::Update(float dt)
{
    t+=dt;
    alphaAnim.Update(dt);

    ring->setPos( screenPos(0.5f*sin(t*2.4), 0.5f*cos(t)) );
    star->setPos( screenPos(0.5f*cos(t*1.6), 0.5f*sin(t)) );
    spark->setPos( screenPos(0.f, -0.6f) );
    runner->setPos(screenPos(-0.2f, 0.0f) );

    static float alpha=0;
    alpha +=dt*124.f;
    while(alpha>255)    alpha-=255.f;
    runner->setColor( QColor(255, 255, 255, alphaAnim.Value()) );

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
    ring->setSize( rectSize(0.2f) );
    star->setSize( rectSize(0.1f) );
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
