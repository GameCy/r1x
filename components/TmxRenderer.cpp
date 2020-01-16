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
                                  , QVector2D tileSize
                                  , QVector2D cellSize)
{
    quadRenderer.ReserveActiveQuads(tileCount);
    int quadIndex=0;
    QColor white(255,255,255,255);
    float cursorY=layer->offset.y() + (layer->size.y()-1)*cellSize.y()+1;
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
            cursorX += cellSize.x();
        }
        cursorY -= cellSize.y();
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
        BuildUVTable(0.2f);
        BuildLayers();
    }
}

TmxRenderer::~TmxRenderer()
{
}

void TmxRenderer::BuildUVTable(float bleedingInset)
{
    uvTable.clear();
    uvTable.push_back( UVRect() ); // gid zero doesn't exist, so fill 1st element
	int gid=1;
    for(auto tileset=map.tilesets.begin(); tileset!=map.tilesets.end(); ++tileset)
	{
        auto &imageDx = tileset->imageWidth;
        auto &imageDy = tileset->imageHeight;
        auto &margin  = tileset->tileMarginInImage;
        auto &spacing = tileset->tileSpacingInImage;
        auto &tileU   = tileset->tileWidth;
        auto &tileV   = tileset->tileHeight;

        for(uint v = margin; (v+tileV)<imageDy; v += (tileV + spacing))
		{
            for(uint u = margin; (u+tileU)<imageDx; u += (tileU+spacing))
            {
                UVRect tile_uvs(  float(u) + bleedingInset
                                , float(v) + bleedingInset
                                , float(u + tileU) - bleedingInset
                                , float(v + tileV) - bleedingInset);
                tile_uvs.Normalize(imageDx, imageDy);
                uvTable.push_back(tile_uvs);
				gid++;
			}
		}
	}
}

Material *TmxRenderer::PrepareMaterial(QString tilesetFilename)
{
    QString tilesetPath = Utils::getFolder(filePath) + "/" + tilesetFilename;

    auto mat = new Material(tilesetPath);
    mat->DepthTesting = false;
    auto texture = mat->GetTexture();
    texture->bind();
    texture->setMinMagFilters(QOpenGLTexture::Nearest, QOpenGLTexture::Nearest);
    return mat;
}

void TmxRenderer::BuildLayers()
{
    auto cellSize = QVector2D(map.tileWidth, map.tileHeight);
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
                auto tilesetFilename = QString::fromStdString( tilesetItr->imagePath );
                auto mat = PrepareMaterial(tilesetFilename);

                int maxQuads = layerItr->size.x() * layerItr->size.x();
                auto tileSize = QVector2D(tilesetItr->tileWidth, tilesetItr->tileHeight);

                auto layer = new TmxLayerRenderer( maxQuads, mat);
                unsigned int minGid = tilesetItr->firstgid;
                unsigned int maxGid = minGid + tilesetItr->tileCount -1;
                layer->BuildQuads( &(*layerItr)
                                   , tileCount
                                   , minGid
                                   , maxGid
                                   , uvTable
                                   , tileSize
                                   , cellSize);
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
    return QRect(layer.offset.x()
                 , layer.offset.y()
                 , layer.offset.x() + layer.size.x()*map.tileWidth - 1
                 , layer.offset.y() + layer.size.y()*map.tileHeight - 1);
}

} // tmxrenderer
