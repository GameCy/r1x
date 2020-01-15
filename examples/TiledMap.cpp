#include "TiledMap.h"


TiledMap::TiledMap()
    : tmxRenderer(":/tiledMaps/testLevel.json")
{
    tilePixelSize = tmxRenderer.getTilePixelSize(0);

    // window viewport in pixels, dummy values, will change in Resize() method
    windowViewport.SetLowerPoint(0,0);
    windowViewport.SetHighPoint(Graphics::Screen.Width()
                                , Graphics::Screen.Height());

    tmxVisibleArea.SetLowerPoint(0,0);
    // fit 8x6 tiles into the window viewport
    tmxVisibleArea.SetHighPoint(tilePixelSize.x()*20.f, tilePixelSize.y()*20.f );

    scrollBoundaries = tmxRenderer.getLayerBoundaries(0);
    //scrollBoundaries.setRight( scrollBoundaries.right());

    Begin(360.f);
}

TiledMap::~TiledMap()
{
}

void TiledMap::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;

    // aply the windowViewport to the openGL context
    // to limit drawing to only a part of the real window
    //windowViewport.GLApply();

    // use the boundaries of the visible area in the rasterShader
    Graphics::rasterShader->UpdateViewport(tmxVisibleArea);

    // render all the layers
    tmxRenderer.Render();

    // restore openGL viewport and rasterShader viewport
    // to full size, for the user interface to render properly
    Graphics::Screen.GLApply();
    Graphics::rasterShader->UpdateViewport( Graphics::Screen );
}

void TiledMap::Update(float dt)
{
    updateWindowViewport();

    // scroll tiles
    float ratio= .5f + 0.5f*sin(Time);
    tmxVisibleArea.X1 = scrollBoundaries.left()-50;
    tmxVisibleArea.X2 = scrollBoundaries.right()+50;
    tmxVisibleArea.Y1 = scrollBoundaries.top()-50;
    tmxVisibleArea.Y2 = scrollBoundaries.bottom()+50;
//    tmxViewport.X1 = ratio*scrollBoundaries.width();
//    tmxViewport.X2 = tmxViewport.X1 + tilePixelSize.x()*8.f;
}

void TiledMap::Resize(ViewPort &screen)
{
    updateWindowViewport();
}

void TiledMap::updateWindowViewport()
{
    auto screen = Graphics::Screen.Size();
    auto t = Time;
    float swing = 0.25f*(1.f+ sin(0.2f*t));
    windowViewport.SetLowerPoint(0, (0.0f+ swing)*screen.y());
    windowViewport.SetHighPoint(screen.x(), (0.5f+swing)*screen.y());
}
