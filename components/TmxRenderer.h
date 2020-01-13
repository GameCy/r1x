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
    void BuildQuads(const tmxparser::Layer_t *layer
                    , unsigned int minGid
                    , unsigned int maxGid
                    , QVector<UVRect> &uvTable
                    , QVector2D tileSize);

private:
    QuadRenderer2DX     quadRenderer;
};


class TmxRenderer
{
public:
    TmxRenderer(QString tmxJsonFilePath);
	~TmxRenderer();
	
    void Render();
    QVector2D getTilePixelSize(unsigned int tilesetIndex);

    QVector<TmxLayerRenderer*>  layers;

private:
	TmxRenderer() {}

    void BuildUVTable();
    void BuildLayers();

    QVector<UVRect>     uvTable;
    tmxparser::Map_t    map;
};

}
#endif 
