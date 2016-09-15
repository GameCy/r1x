#ifndef QUADRENDERER_H
#define QUADRENDERER_H
#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>
#include <vector>
#include <QOpenGLTexture>
#include "TextureAnim.h"

#define INVALID_OGL_VALUE 0xffffffff

struct Particle {
    QVector3D	pos;
    QVector3D	speed;
    float		t;
    unsigned short animFrameIndex;
};

typedef std::vector<Particle>   ParticleVec;

struct ParticleQuad
{
    QVector3D   pos1;
    QVector2D   UV1;
    QVector3D   pos2;
    QVector2D   UV2;
    QVector3D   pos3;
    QVector2D   UV3;
    QVector3D   pos4;
    QVector2D   UV4;
};


class QuadRenderer
{
public:
    QuadRenderer(int maxQuads,  TextureAnimPtr texAnim);
    virtual ~QuadRenderer();

    void    ClearQuads();
    ParticleQuad& getQuad(int idx);

    void    reserveActiveQuads(int numQuads);
    void    UpdateQuadsBuffer();
    void	RenderQuads();

private:

    std::vector<ParticleQuad>  quads;
    GLuint  quadsBuffer;
    std::vector<unsigned short>  indices;
    GLuint  indicesBuffer;
    GLuint  ActiveQuads;

    //Material        texture; if no texAnim, activate material instead?
    TextureAnimPtr  textureAnim;

    void InitIndices(int numQuads);
};

#endif // QUADRENDERER_H
