#include "TiledMap.h"


TiledMap::TiledMap()
    : tmxRenderer(":/tiledMaps/testLevel.json")
{
    // window viewport in pixels, dummy values, will change in Resize() method
    windowViewport.SetLowerPoint(0,0);
    windowViewport.SetHighPoint(320,240);

    tmxViewport.SetLowerPoint(0,0);
    // get tile size from tileset 0 in pixels
    auto tilePixelSize = tmxRenderer.getTilePixelSize(0);
    // fit 8x6 tiles into the window viewport
    tmxViewport.SetHighPoint(tilePixelSize.x()*8.f, tilePixelSize.y()*6.f );

    Begin(360.f);
}

TiledMap::~TiledMap()
{
}

void TiledMap::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;

    ogl.glViewport(windowViewport.X1, windowViewport.Y1, windowViewport.Width(), windowViewport.Height());
    Graphics::rasterShader->UpdateViewport(tmxViewport);

    tmxRenderer.Render();
}

void TiledMap::Update(float dt)
{
    float ratio= .5f + 0.5f*sin(Time);

    // move render viewport diagonally accross the screen/window
    auto lowerPos = ratio*halfScreen;
    windowViewport.SetLowerPoint(lowerPos.x(), lowerPos.y());
    auto highPos = lowerPos + halfScreen;
    windowViewport.SetHighPoint(highPos.x(), highPos.y());

    // scroll tiles
    tmxViewport.X1 = TimeRatio()*halfScreen.x();
    tmxViewport.X2 = tmxViewport.X1 + halfScreen.x();
}

void TiledMap::Resize(ViewPort &screen)
{
    halfScreen = 0.5f*screen.Size();
    windowViewport.SetLowerPoint(0,0);
    windowViewport.SetHighPoint(halfScreen.x(), halfScreen.y());
}
