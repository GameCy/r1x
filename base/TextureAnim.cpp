#include "TextureAnim.h"
#include "QuadRenderer3D.h"
#include <math.h>

TextureAnim::TextureAnim(TexAnimParams params)
{
    Init(params.texturePath, params.dt, params.dx, params.dy, params.maxFrame);
}

TextureAnim::TextureAnim(QString textureUrl, float animDT, int numFramesX, int numFramesY, int maxFrames)
{
    Init( textureUrl, animDT, numFramesX, numFramesY, maxFrames);
}

TextureAnim::~TextureAnim()
{}

void	TextureAnim::Init(QString  textureUrl, float animDT, int	numFramesX, int	numFramesY, int maxFrames)
{
    material = new Material( textureUrl );
    if (!material || (!material->isTextureCreated()))
    {
        printf("failed to load '%s'\n", textureUrl.toStdString().c_str());
    }

	AnimDT = animDT;
	MaxFrames = maxFrames;
	FramesX = numFramesX;
	FramesY = numFramesY;
	cellDx = 1.0f/float(numFramesX);
	cellDy = 1.0f/float(numFramesY);
}

int		TextureAnim::CalcCellIdx(float time)
{
    if (time<0.f)   return -1;
    float ratio = time/AnimDT;
	int idx = (int) (ratio*((float)MaxFrames));
	if (idx<0)			idx = 0;
	if (idx>=MaxFrames)	idx = MaxFrames-1;
	return idx;
}

void	TextureAnim::CalcUVs(int cellIdx, Quad3D &quad)
{
	int idx_x = cellIdx;
	int idx_y = 0;
	while(idx_x>=FramesX)
	{
		idx_x -= FramesX;
		idx_y++;
	}
	float uvx = float(idx_x)*cellDx;
	float uvy = float(idx_y)*cellDy;

	const float margin = 0.01f;

    quad.U1= uvx + margin;          quad.V1 = uvy+cellDy - margin;
    quad.U3 = uvx+cellDx - margin;	quad.V3 = uvy + margin;
    quad.U2 = uvx+cellDx - margin;	quad.V2 = uvy+cellDy - margin;
    quad.U4 = uvx + margin;			quad.V4 = uvy + margin;
}

