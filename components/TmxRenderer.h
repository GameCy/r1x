#ifndef _TMX_RENDERER_H_
#define _TMX_RENDERER_H_
#include <QVector2D>
#include "TmxJsonParser.h"


namespace tmxparser
{


typedef struct TileMappingInfo_t
{
public:
    TileMappingInfo_t(int gid, int tx, int ty) { tilesetIndex=gid; srcOffset.setX(tx); srcOffset.setY(ty); }

	int			tilesetIndex;
    QVector2D	srcOffset;
} TileMappingInfo_t;

typedef std::vector<TileMappingInfo_t>		TileMappingCollection_t;


class TmxRenderer
{
public:
	TmxRenderer(Map_t* map);
	~TmxRenderer();
	
	// render without resizing tiles
    void Render(QVector2D offset);

	// render each tile, scaled to a new cell size
    void Render(QVector2D offset, QVector2D destCellSize);

	// 0,0 destCellSize renders at map tile size
    //void RenderLayer(int layerIdx, Point_t offset, QVector2D destCellSize);

private:
	TmxRenderer() {}

    //void LoadResources();
    //void DestroyResources();
    //void Precalculate();
    //bool isTileVisible(Point_t destination);

	TileMappingCollection_t		gidTable; // to translate gid's to tileIndex,tile Location pairs,

    //CIw2DImage** TilesetImages; // replace this with some texture or material
	int numSets;

    // sizes depend on viewport , so , tile size can be float, even display size and starting point
    //Point_t displaySize;
    //Point_t displayTileSize;

	Map_t* map;
};

}
#endif 
