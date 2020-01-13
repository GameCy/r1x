#include "TiledMap.h"


TiledMap::TiledMap()
    : tmxRenderer(":/tiledMaps/testLevel.json")
{
    tilePixelSize = tmxRenderer.getTilePixelSize(0);

    // window viewport in pixels, dummy values, will change in Resize() method
    windowViewport.SetLowerPoint(0,0);
    windowViewport.SetHighPoint(Graphics::Screen.Width()
                                , Graphics::Screen.Height());

    tmxViewport.SetLowerPoint(0,0);
    // fit 8x6 tiles into the window viewport
    tmxViewport.SetHighPoint(tilePixelSize.x()*8.f, tilePixelSize.y()*6.f );

    scrollBoundaries = tmxRenderer.getLayerBoundaries(0);
    scrollBoundaries.setRight( scrollBoundaries.right() - 8*tilePixelSize.x());

    Begin(360.f);
}

TiledMap::~TiledMap()
{
}

void TiledMap::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;

    windowViewport.GLApply();
    Graphics::rasterShader->UpdateViewport(tmxViewport);

    tmxRenderer.Render();

    // restore viewport to full size for user interface
    auto screen = Graphics::Screen;
    ogl.glViewport(screen.X1, screen.Y1, screen.Width(), screen.Height());
    Graphics::rasterShader->UpdateViewport( screen );
}

void TiledMap::Update(float dt)
{
    float ratio= .5f + 0.5f*sin(Time);

    // move render viewport diagonally accross the screen/window
    auto lowerPos = ratio*halfScreen;
    //windowViewport.SetLowerPoint(lowerPos.x(), lowerPos.y());
    auto highPos = lowerPos + halfScreen;
    //windowViewport.SetHighPoint(highPos.x(), highPos.y());

    // scroll tiles
    tmxViewport.X1 = ratio*scrollBoundaries.width();
    tmxViewport.X2 = tmxViewport.X1 + tilePixelSize.x()*8.f;
}

void TiledMap::Resize(ViewPort &screen)
{
    halfScreen = 0.5f*screen.Size();
    windowViewport.SetLowerPoint(0,0);
    windowViewport.SetHighPoint(halfScreen.x(), halfScreen.y());
}
