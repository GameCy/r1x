#include "QuadRenderer.h"
#include <math.h>

TextureAnim::TextureAnim()
	: MaxFrames(0) , FramesX(0), FramesY(0)
	, AnimDT(0)
	, cellDx(0) , cellDy(0)
{}

TextureAnim::~TextureAnim()
{}


TextureAnimPtr TextureAnim::Create(QString textureUrl, float animDT, int numFramesX, int numFramesY, int maxFrames)
{
    TextureAnimPtr ret=0;

    QOpenGLTexture* tex = new QOpenGLTexture( QImage(textureUrl));
    if (tex && tex->isCreated())
	{
		ret = new TextureAnim();
		ret->Init( tex , animDT, numFramesX, numFramesY, maxFrames);
	}
    else
    {
        printf("failed to load '%s'\n", textureUrl.toStdString().c_str());
    }
	return ret;
}

void	TextureAnim::Init(QOpenGLTexture* texture, float animDT, int	numFramesX, int	numFramesY, int maxFrames)
{
    material.texture =  texture;
	
	AnimDT = animDT;
	MaxFrames = maxFrames;
	FramesX = numFramesX;
	FramesY = numFramesY;
	cellDx = 1.0f/float(numFramesX);
	cellDy = 1.0f/float(numFramesY);
}

int		TextureAnim::CalcCellIdx(float time)
{
	float ratio = 1.0f - fabs(1.0f - time/AnimDT);
	int idx = (int) (ratio*((float)MaxFrames));
	if (idx<0)			idx = 0;
	if (idx>=MaxFrames)	idx = MaxFrames-1;
	return idx;
}

void	TextureAnim::CalcUVs(int cellIdx, ParticleQuad &quad)
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

    quad.UV1.setX( uvx + margin );			quad.UV1.setY( uvy+cellDy - margin );
    quad.UV2.setX( uvx+cellDx - margin );	quad.UV2.setY( uvy+cellDy - margin );
    quad.UV3.setX( uvx+cellDx - margin );	quad.UV3.setY( uvy + margin );
    quad.UV4.setX( uvx + margin );			quad.UV4.setY( uvy + margin );
}

