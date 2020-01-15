#include "TmxRenderer.h"
#include <Graphics.h>
#include "Utils.h"

namespace tmxrenderer
{

using namespace tmxparser;

TmxLayerRenderer::TmxLayerRenderer(int maxTiles, MaterialPtr mat)
    : quadRenderer(maxTiles, mat)
{
}

void TmxLayerRenderer::Render()
{
    quadRenderer.RenderQuads();
}

void TmxLayerRenderer::BuildQuads(const Layer_t *layer
                                  , unsigned int tileCount
                                  , unsigned int minGid
                                  , unsigned int maxGid
                                  , QVector<UVRect> &uvTable
                                  , QVector2D tileSize)
{
    quadRenderer.ReserveActiveQuads(tileCount);
    int quadIndex=0;
    QColor white(255,255,255,255);
    float cursorY=layer->offset.y() + (layer->size.y()-1)*tileSize.y()+1;
    unsigned int tileIndex=0;
    for(int row=0; row<layer->size.y(); ++row)
    {
        float cursorX=layer->offset.x();
        for(int column=0; column<layer->size.x(); ++column)
        {
            auto gid = layer->tiles[tileIndex];
            if ( (gid>=minGid) && (gid<=maxGid))
            {
                Quad2DX &quad = quadRenderer.getQuad(quadIndex);
                quad.SetUVRect( uvTable[gid] );
                quad.SetGeometry(cursorX, cursorY, tileSize.x(), tileSize.y());
                quad.SetAllColors(white);

                quadIndex++;
            }
            ++tileIndex;
            cursorX += tileSize.x();
        }
        cursorY -= tileSize.y();
    }
    quadRenderer.UpdateQuadsBuffer();
}

// -----------------------------------------------

TmxRenderer::TmxRenderer(QString tmxJsonFilePath)
    : filePath(tmxJsonFilePath)
{
    parseTmxFromJSON_file(filePath, &map);
    if (map.layers.size()>0)
    {
        BuildUVTable();
        BuildLayers();
    }
}

TmxRenderer::~TmxRenderer()
{
}

void TmxRenderer::BuildUVTable()
{
    uvTable.clear();
    uvTable.push_back( UVRect() ); // gid zero doesn't exist, so fill 1st element
	int gid=1;

    for(auto tileset=map.tilesets.begin(); tileset!=map.tilesets.end(); ++tileset)
	{
        float tileU = float(tileset->tileWidth)/float(tileset->imageWidth);
        float tileV = float(tileset->tileHeight)/float(tileset->imageHeight);
        // margin .25  of a pixel
        float marginU = 0.25f/float(tileset->imageWidth);
        float marginV = 0.25f/float(tileset->imageHeight);
        for(float v = 0; v<1.0f; v+=tileV)
		{
            for(float u = 0; u<1.0f; u+=tileU)
			{
                uvTable.push_back( UVRect(u, v, u + tileU - marginU, v + tileV - marginV) );
				gid++;
			}
		}
	}
}

void TmxRenderer::BuildLayers()
{
    int layerIndex = 0;
    auto layerItr = map.layers.cbegin();
    for( ; layerItr!=map.layers.end(); ++layerItr)
    {
        int tilesetIndex=0;
        auto tilesetItr = map.tilesets.begin();
        for( ; tilesetItr!=map.tilesets.end(); ++tilesetItr)
        {

            int tileCount = tmxparser::CountLayerTilesetUsage(map, layerIndex, tilesetIndex);
            if (tileCount<=0)
            {
                layers.push_back(nullptr);
            }
            else
            {
                QString tilesetPath = Utils::getFolder(filePath) + "/" + QString::fromStdString( tilesetItr->imagePath );

                auto mat = new Material(tilesetPath);
                mat->DepthTesting = false;
                int maxQuads = layerItr->size.x() * layerItr->size.x();
                auto tileSize = QVector2D(tilesetItr->tileWidth, tilesetItr->tileHeight);

                auto layer = new TmxLayerRenderer( maxQuads, mat);
                unsigned int minGid = tilesetItr->firstgid;
                unsigned int maxGid = minGid + tilesetItr->tileCount -1;
                layer->BuildQuads( &(*layerItr), tileCount, minGid, maxGid, uvTable, tileSize);
                layers.push_back(layer);
            }
            ++tilesetIndex;
        }
        ++layerIndex;
    }
}

void TmxRenderer::Render()
{
    auto layerItr = layers.begin();
    for( ; layerItr!=layers.end(); ++layerItr)
    {
        auto layer = *layerItr;
        if (layer)
            layer->Render();
    }
}

QPoint TmxRenderer::getTilePixelSize(unsigned int tilesetIndex)
{
    auto &tileset = map.tilesets[tilesetIndex];
    return QPoint(tileset.tileWidth, tileset.tileHeight);
}

QRect TmxRenderer::getLayerBoundaries(unsigned int layerIndex)
{
    auto &layer = map.layers[layerIndex];
    auto &tileset = map.tilesets[0]; // cheating
    return QRect(layer.offset.x()
                 , layer.offset.y()
                 , layer.offset.x() + layer.size.x()*tileset.tileWidth
                 , layer.offset.y() + layer.size.y()*tileset.tileHeight );
}

} // tmxrenderer
