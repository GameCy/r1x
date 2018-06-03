#include "UVRectArray.h"

UVRectArray::UVRectArray()
    : MaxElement(0)
    , UVS(0)
{}

UVRectArray::~UVRectArray()
{
    if (UVS)
        delete[] UVS;
    UVS=0;
}

UVRect *UVRectArray::Get(int element)
{ return &UVS[element]; }

UVRect &UVRectArray::operator [](int element)
{ return UVS[element]; }

void UVRectArray::AllocateFrames(int numFrames)
{
    if (UVS)    delete UVS;
    MaxElement = numFrames;
    UVS = new UVRect[MaxElement];
}

void UVRectArray::InitCellsFromAtlas(AtlasImporter &atlas, std::vector<QString> &cellNames)
{
    AllocateFrames(cellNames.size());
    for(int n=0; n<MaxElement; ++n)
    {
        atlas.GetUVRect( cellNames[n], UVS[n]);
    }
}

void UVRectArray::InitCellsFromGrid(int numFramesX, int numFramesY, int maxFrames, UVRect *allUVRect)
{
    AllocateFrames(maxFrames);

    UVRect allCells(0,0,1,1);
    if (allUVRect)
        allCells = *allUVRect;

    float cellDx = (allCells.U2 - allCells.U1)/float(numFramesX);
    float cellDy = (allCells.V2 - allCells.V1)/float(numFramesY);
    for(int n=0; n<maxFrames; ++n)
        CalcCellUVs(n, UVS[n], allCells, numFramesX, cellDx, cellDy);
}


void UVRectArray::CalcCellUVs(int cellIndex, UVRect &result, UVRect &allCells
                              , int columns, float cellDx, float cellDy)
{
    int row = 0;
    while(cellIndex>=columns)
    {
        cellIndex -= columns;
        row++;
    }
    float uvx = allCells.U1 + float(cellIndex)*cellDx;
    float uvy = allCells.V1 + float(row)*cellDy;

    const float margin = 0.0001f;
    result.U1= uvx + margin;          result.V1 = uvy + margin;
    result.U2= uvx + cellDx - margin; result.V2 = uvy + cellDy - margin;
}
