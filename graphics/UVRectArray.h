#ifndef UVRECTARRAY_H
#define UVRECTARRAY_H
#include "UVRect.h"
#include "AtlasImporter.h"

class UVRectArray
{
public:
    UVRectArray();
    ~UVRectArray();

    void InitCellsFromAtlas(AtlasImporter &atlas, QStringList &cellNames);
    void InitCellsFromGrid(int numFramesX, int numFramesY, int maxFrames, UVRect *allUVRect=nullptr);

    UVRect *Get(int element);
    const UVRect &operator [](int element);

    int MaxElement;
private:
    UVRect* UVS;

    void AllocateFrames(int numFrames);

    static void CalcCellUVs(int cellIndex, UVRect &result, UVRect &allCells, int columns, float cellDx, float cellDy);
};

#endif // UVRECTARRAY_H
