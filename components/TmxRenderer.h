#ifndef TMXRENDERER_H_
#define TMXRENDERER_H_
#include <QVector2D>
#include "TmxJsonParser.h"
#include "SpriteMap.h"
#include "ViewPort.h"

namespace tmxrenderer
{

class TmxLayerRenderer
{
public:
    TmxLayerRenderer(int maxTiles, MaterialPtr mat);

    void Render();
    void ResizeTiles(QVector2D newTileSize);
    void MoveLayer(QVector2D center);
    void BuildQuads(const tmxparser::Layer_t *layer, unsigned int minGid, unsigned int maxGid, QVector<UVRect> &uvTable);

    QVector2D           tileSize;
    QuadRenderer2DX     quadRenderer;
};

class TmxRenderer
{
public:
    TmxRenderer(tmxparser::Map_t* map);
	~TmxRenderer();
	
    void Render();

    QVector<TmxLayerRenderer*>  layers;

private:
	TmxRenderer() {}

    void BuildUVTable();
    void BuildLayers();
    void BuildQuads(QuadRendererBase* renderer, int layerIndex, int tilesetIndex);

    QVector<UVRect>     uvTable;
    tmxparser::Map_t*   map;

};

}
#endif 
