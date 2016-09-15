#ifndef _TEXTURE_ANIM_
#define _TEXTURE_ANIM_
#include "SmartPtr.h"
#include <QVector2D>
#include "Material.h"

class ParticleQuad;

class TextureAnim;
typedef	SmartPtr<TextureAnim>	TextureAnimPtr;

class TextureAnim : public RefCountBase
{
public:
	TextureAnim();
	virtual ~TextureAnim();
	
    static TextureAnimPtr Create(QString texureUrl, float animDT=0.7f, int	numFramesX=5, int	numFramesY=5, int maxFrames=25);

    void	Init(QOpenGLTexture* texture, float animDT, int	numFramesX, int	numFramesY, int maxFrames);

    int		CalcCellIdx(float time);
    void	CalcUVs(int cellIdx,  ParticleQuad &quad);

    Material	material;
	float		AnimDT;

private:
	int		MaxFrames;
	int		FramesX;
	int		FramesY;

	float	cellDx, cellDy;
};

#endif
