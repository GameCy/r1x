#ifndef TILEDMAP_H
#define TILEDMAP_H
#include "ExampleBase.h"
#include "Graphics.h"
#include "Camera.h"
#include "TmxJsonParser.h"
#include "TmxRenderer.h"

class TiledMap : public ExampleBase
{
public:
    TiledMap();
    virtual ~TiledMap();

    // Temporal interface
    void Update(float dt);
    // ExampleBase interface
    void Render();
    void Resize(ViewPort &screen);

private:
    ViewPort    windowViewport;
    ViewPort    tmxViewport;

    tmxrenderer::TmxRenderer tmxRenderer;

    QVector2D   halfScreen;
};

#endif // TILEDMAP_H
