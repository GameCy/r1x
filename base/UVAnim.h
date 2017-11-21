#ifndef _TEXTURE_ANIM_
#define _TEXTURE_ANIM_
#include <QVector2D>
#include "AtlasImporter.h"

class Quad3D;

class UVAnim
{
public:
    UVAnim();
    UVAnim(float animDT, int numFramesX, int numFramesY, int maxFrames, UVRect *atlasUVRect=0);

    void	Init(float animDT, int	numFramesX, int	numFramesY, int maxFrames, UVRect *atlasUVRect=0);

    UVRect  getCellUVs(float time);

    int		CalcCellIdx(float time);
    void	CalcUVs(int cellIdx,  Quad3D &quad);

	float		AnimDT;

private:
    int		MaxFrames;
	int		FramesX;
	int		FramesY;

	float	cellDx, cellDy;

    UVRect  uvRect;
};

#endif
