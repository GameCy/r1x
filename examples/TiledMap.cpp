#include "TiledMap.h"
#include <math.h>

TiledMap::TiledMap()
    //: tmxRenderer(":/tiledMaps/testLevel.json")
    : tmxRenderer(":/tiledMaps/desertLand.json")
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
    windowViewport.GLApply();
    ogl.glScissor(windowViewport.X1, windowViewport.Y1, windowViewport.Width(), windowViewport.Height());
    ogl.glEnable(GL_SCISSOR_TEST);
    ogl.glClearColor(0.1f, 0.35f, 0.1f,0);
    ogl.glClear(GL_COLOR_BUFFER_BIT);

    // use the boundaries of the visible area in the rasterShader
    Graphics::rasterShader->UpdateViewport(tmxVisibleArea);

    // render all the layers
    tmxRenderer.Render();

    // restore openGL viewport and rasterShader viewport
    // to full size, for the user interface to render properly
    ogl.glDisable(GL_SCISSOR_TEST);
    Graphics::Screen.GLApply();
    Graphics::rasterShader->UpdateViewport( Graphics::Screen );
}

void TiledMap::Update(float dt)
{
    updateWindowViewport();

    float zoom = 0.16f +0.1f*sin(0.55f*Time);
    // scroll X-axis
    int offsetX = scrollBoundaries.width()*(0.25f +0.25f*sin(0.4f*Time));
    tmxVisibleArea.X1 = offsetX + scrollBoundaries.left();
    tmxVisibleArea.X2 = tmxVisibleArea.X1
                        + scrollBoundaries.width()*zoom;
    // scroll Y-axis
    int offsetY = scrollBoundaries.height()*(0.25f +0.25f*sin(0.25f*Time));
    tmxVisibleArea.Y1 = offsetY + scrollBoundaries.top();
    tmxVisibleArea.Y2 = tmxVisibleArea.Y1
                        + scrollBoundaries.height()*zoom/Graphics::DPI.VIEWPORT_ASPECT_RATIO;
}

void TiledMap::Resize(ViewPort &screen)
{
    updateWindowViewport();
}

void TiledMap::updateWindowViewport()
{
    auto screen = Graphics::Screen.Size();
    auto dx = screen.x();
    auto dy = screen.y();
    auto t = Time;
    float swing = 0.25f*(1.f+ sin(0.2f*t));
    windowViewport.SetLowerPoint(0.1f*dx, (0.0f+ swing)*dy);
    windowViewport.SetHighPoint(0.9*dx, (0.5f+swing)*dy);
}
