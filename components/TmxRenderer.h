#ifndef TMXRENDERER_H_
#define TMXRENDERER_H_
#include <QVector2D>
#include "TmxJsonParser.h"
#include "SpriteMap.h"
#include "ViewPort.h"
#include <QRect>

namespace tmxrenderer
{

class TmxLayerRenderer
{
public:
    TmxLayerRenderer(int maxTiles, MaterialPtr mat);

    void Render();
    void BuildQuads(const tmxparser::Layer_t *layer
                    , unsigned int tileCount
                    , unsigned int minGid
                    , unsigned int maxGid
                    , QVector<UVRect> &uvTable
                    , QVector2D tileSize, QVector2D cellSize);

private:
    QuadRenderer2DX     quadRenderer;
};


class TmxRenderer
{
public:
    TmxRenderer(QString tmxJsonFilePath);
	~TmxRenderer();
	
    void Render();

    QPoint getTilePixelSize(unsigned int tilesetIndex);
    QRect getLayerBoundaries(unsigned int layerIndex);

    QVector<TmxLayerRenderer*>  layers;


private:
	TmxRenderer() {}

    void BuildUVTable(float bleedingInset);
    void BuildLayers();
    Material* PrepareMaterial(QString tilesetFilename);

    QString filePath;
    QVector<UVRect>     uvTable;
    tmxparser::Map_t    map;
};

}
#endif 
