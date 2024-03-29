#include "SpriteParticleFade.h"
#include "Graphics.h"
#include "Core.h"
#include <math.h>

bool colorPerSprite = true;

SpriteParticleFade::SpriteParticleFade()
    : atlas(50, ":/textures/textures.atlas", colorPerSprite)
    , trigonometricParameter(0.8, 3.0, 6.f)
{
    screenWidth = Graphics::Screen.Width();
    screenHeight= Graphics::Screen.Height();

    for(int i=0; i<50; ++i)
    {
        star[i] = atlas.CreateSprite("star_particle.png");
        starTime[i] = Core::Random.GetFloat(0.f, 6.285f);
    }

    atlas.GetMaterial()->Blending = true;
    atlas.GetMaterial()->DepthTesting = false;

    trigonometricParameter.Repeat(2000);
    Resize( Graphics::Screen );

    Begin( 2.0*M_PI );
}

SpriteParticleFade::~SpriteParticleFade()
{
}

void SpriteParticleFade::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;

    Graphics::rasterShader->UseColorPerVertex(true);
        atlas.Render();
    Graphics::rasterShader->UseColorPerVertex(false);
}

void SpriteParticleFade::Update(float dt)
{
    if (IsFinished())
        Begin(2.0*M_PI);

    trigonometricParameter.Update(dt);
    float trig = trigonometricParameter.Value();
    for(int i=0; i<50; ++i)
    {
        float st = Time + starTime[i];
        star[i]->setPos( screenPos(0.5f*sin(st*trig), 0.5f*cos(st)) );
        star[i]->setColor( QColor(122+40*trig, 122-40*trig, 255, 128+120*sin(st+trig)) );
    }

    atlas.Update();
}

void SpriteParticleFade::Resize(ViewPort &screen)
{
    screenWidth = screen.Width();
    screenHeight = screen.Height();
    for(int i=0; i<50; ++i)
        star[i]->setSize( rectSize(0.2f) );
}

QVector2D SpriteParticleFade::rectSize(float size)
{
    float W = screenWidth*size;
    float H = W * Graphics::DPI.VIEWPORT_ASPECT_RATIO;
    return QVector2D(W,H);
}

QVector2D SpriteParticleFade::rectSize(float sx, float sy)
{
    float W = sx*screenWidth;
    float H = sy*screenHeight * Graphics::DPI.VIEWPORT_ASPECT_RATIO;
    return QVector2D(W,H);
}

QVector2D SpriteParticleFade::screenPos(float x, float y)
{
    float px = screenWidth*( 1.f + x)/2.f;
    float py = screenHeight*(1.f + y)/2.f;
    return QVector2D(px,py);
}
