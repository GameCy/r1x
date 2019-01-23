#include "TmxRenderer.h"

namespace tmxparser
{

	
TmxRenderer::TmxRenderer(Map_t* pMap)
	: map(pMap)
{
    //LoadResources();
    //Precalculate();
    //displayWidth = IwGxGetDisplayWidth();
    //displayHeight = IwGxGetDisplayHeight();

}
TmxRenderer::~TmxRenderer()
{
    //DestroyResources();
}
/*
void TmxRenderer::LoadResources()
{
	int t;
	numSets = map->tilesets.size(); 
	TilesetImages = new CIw2DImage*[numSets];
	for(t=0; t<numSets; ++t)
	{
		std::string path = map->tilesets[t].imagePath;
		TilesetImages[t] = Iw2DCreateImage(path.c_str());
	}
}

void TmxRenderer::DestroyResources()
{
	if (TilesetImages)
	{
		for(int t=0; t<numSets; ++t)
			delete TilesetImages[t];
		delete TilesetImages;
	}
}

void TmxRenderer::Precalculate()
{
	gidTable.clear();
	gidTable.push_back( TileMappingInfo_t (-1,0,0) ); // gid zero doesn't exist, so fill 1st element
	int gid=1;
	int tilesetIndex=0;

	TilesetCollection_t::iterator tileset;
	for(tileset=map->tilesets.begin(); tileset!=map->tilesets.end(); ++tileset)
	{
		for(int ty = 0; ty<tileset->imageHeight; ty+=tileset->tileHeight)
		{
			for(int tx = 0; tx<tileset->imageWidth; tx+=tileset->tileWidth)
			{
				gidTable.push_back( TileMappingInfo_t(tilesetIndex, tx, ty) );
				gid++;
			}
		}
		tilesetIndex++;
	}
}

*/
/*
void TmxRenderer::Render(QVector2D offset)
{
	int numLayers = map->layers.size();
	for(int l=0; l<numLayers; ++l)
        RenderLayer(l, offset, QVector2D(0,0));
}

void TmxRenderer::Render(QVector2D offset, QVector2D destCellSize)
{
	int numLayers = map->layers.size();
	for(int l=0; l<numLayers; ++l)
		RenderLayer(l, offset, destCellSize);
}

bool TmxRenderer::isTileVisible(Point_t destination)
{
    return  ( -displayTileSize.x < destination.x) && (destination.x< displaySize.x) &&
            ( -displayTileSize.y < destination.y) && (destination.y< displaySize.y);
}

void TmxRenderer::RenderLayer(int layerIdx, Point_t offset, QVector2D destCellSize)
{
	Layer_t* layer = &map->layers[layerIdx];
	TileArray_t* cells = &layer->tiles;
	if (cells->size()==0)	return;
	int cellIndex=0;
	int setIndex;
	int tileWidth, tileHeight;
	
	bool pixel_to_pixel = false;
    if (destCellSize.x()==0 && destCellSize.y()==0)
	{
        displayTileSize.setX(map->tileWidth);
        displayTileSize.setY(map->tileHeight);
		pixel_to_pixel = true;
	}
	else displayTileSize = destCellSize;

    Point_t destination = -offset + layer->startPoint;
    for(int y=0; y<layer->size.y; ++y)
	{
        for(int x=0; x<layer->size.x ++x)
		{
			int gid = cells->at(cellIndex);
			if (gid>0 && isTileVisible(destination))
			{
				TileMappingInfo_t* info = &gidTable[gid];
				setIndex = info->tilesetIndex;
                QVector2D srcSize( map->tilesets[setIndex].tileWidth
								, map->tilesets[setIndex].tileHeight);

				if (pixel_to_pixel)
					Iw2DDrawImageRegion(TilesetImages[setIndex]
									, destination
									, info->srcOffset
									, srcSize);
				else
					Iw2DDrawImageRegion(TilesetImages[setIndex]
									, destination
									, displayTileSize
									, info->srcOffset
									, srcSize);
			}
			cellIndex++;
			destination.x += displayTileSize.x;
		}
		destination.x = -offset.x;
		destination.y += displayTileSize.y;
	}
}
*/
/*
void TmxMarmaladeRenderer::RenderLayer(int layerIdx, CIwFVec2 offset)
{
	Layer_t* layer = &map->layers[layerIdx];
	TileArray_t* cells = &layer->tiles;
	if (cells->size()==0)	return;
	int cellIndex=0;
	int setIndex;
	int tileWidth, tileHeight;
	displayTileSize.x = map->tileWidth;
	displayTileSize.y = map->tileHeight;

	CIwFVec2 destination = -offset + CIwVec2(layer->x,layer->y); 
	for(int y=0; y<layer->height; ++y)
	{
		for(int x=0; x<layer->width; ++x)
		{
			int gid = cells->at(cellIndex);
			if (gid>0 && isTileVisible(destination))
			{
				TileMappingInfo_t* info = &gidTable[gid];
				setIndex = info->tilesetIndex;
				CIwFVec2 srcSize( map->tilesets[setIndex].tileWidth
								, map->tilesets[setIndex].tileHeight);

				Iw2DDrawImageRegion(TilesetImages[setIndex]
									, destination
									, info->srcOffset
									, srcSize);
			}
			cellIndex++;
			destination.x += map->tileWidth;
		}
		destination.x = -offset.x;
		destination.y += map->tileHeight;
	}
}
*/
}
