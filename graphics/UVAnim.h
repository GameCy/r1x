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

    void	Init(float animDuration, int	numFramesX, int	numFramesY, int maxFrames, UVRect *atlasUVRect=0);

    void    Update(float dt);
    UVRect  GetCellUVs();

    UVRect  GetCellUVs(float time);
    int		CalcCellIdx(float time);
    void	CalcUVs(int cellIdx,  Quad3D &quad);

    float		Time;
    float       Duration;

private:
    int		MaxFrames;
	int		FramesX;
	int		FramesY;

	float	cellDx, cellDy;

    UVRect  uvRect;
};

#endif
