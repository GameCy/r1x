#ifndef _TEXTURE_ANIM_
#define _TEXTURE_ANIM_
#include "SmartPtr.h"
#include <QVector2D>
#include "Material.h"

class Quad3D;

struct TexAnimParams {
    QString texturePath;
    float dt;
    int dx, dy, maxFrame;
};

class TextureAnim : public RefCountBase
{
public:
    TextureAnim(TexAnimParams params);
    TextureAnim(QString textureUrl, float animDT=0.7f, int	numFramesX=5, int	numFramesY=5, int maxFrames=25);
	virtual ~TextureAnim();

    int		CalcCellIdx(float time);
    void	CalcUVs(int cellIdx,  Quad3D &quad);

    MaterialPtr	material;
	float		AnimDT;

private:
    void	Init(QString textureUrl, float animDT, int	numFramesX, int	numFramesY, int maxFrames);

    int		MaxFrames;
	int		FramesX;
	int		FramesY;

	float	cellDx, cellDy;
};

typedef	SmartPtr<TextureAnim>	TextureAnimPtr;

#endif
