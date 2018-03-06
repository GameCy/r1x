#include "UVAnim.h"
#include "QuadTypes.h"
#include <math.h>

UVAnim::UVAnim()
 : Time(0)
 , Duration(1.f)
 , MaxFrames(0)
 , FramesX(0)
 , FramesY(0)
 , cellDx(0)
 , cellDy(0)
{
}

UVAnim::UVAnim(float animDuration, int numFramesX, int numFramesY, int maxFrames, UVRect *atlasUVRect)
{
    Init( animDuration, numFramesX, numFramesY, maxFrames, atlasUVRect);
}

void	UVAnim::Init(float animDuration, int	numFramesX, int	numFramesY, int maxFrames, UVRect* atlasUVRect)
{
    if (atlasUVRect)
        uvRect = *atlasUVRect;
    else
        uvRect =  UVRect(0,0,1,1);
    Duration = animDuration;
	MaxFrames = maxFrames;
	FramesX = numFramesX;
	FramesY = numFramesY;
    cellDx = (uvRect.U2 - uvRect.U1)/float(numFramesX);
    cellDy = (uvRect.V2 - uvRect.V1)/float(numFramesY);
}

void UVAnim::Update(float dt)
{
    Time += dt;
    while (Time>Duration)
        Time -= Duration;
}

UVRect UVAnim::GetCellUVs()
{
    return GetCellUVs(Time);
}

UVRect UVAnim::GetCellUVs(float time)
{
    int idx =  CalcCellIdx(time);
    return GetCellUVs(idx);
}

UVRect UVAnim::GetCellUVs(int cellIndex)
{
    UVRect cellUVs;

    int idx_x = cellIndex;
    int idx_y = 0;
    while(idx_x>=FramesX)
    {
        idx_x -= FramesX;
        idx_y++;
    }
    float uvx = uvRect.U1 + float(idx_x)*cellDx;
    float uvy = uvRect.V1 + float(idx_y)*cellDy;

    const float margin = 0.0001f;
    cellUVs.U1= uvx + margin;          cellUVs.V1 = uvy + margin;
    cellUVs.U2= uvx + cellDx - margin; cellUVs.V2 = uvy + cellDy - margin;
    return cellUVs;
}

int		UVAnim::CalcCellIdx(float time)
{
    if (time<0.f)   return 0;
    if (time>Duration) return MaxFrames-1;
    float ratio = time/Duration;
	int idx = (int) (ratio*((float)MaxFrames));
	if (idx<0)			idx = 0;
	if (idx>=MaxFrames)	idx = MaxFrames-1;
	return idx;
}

