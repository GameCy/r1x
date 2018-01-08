#ifndef QUADRENDERER3D_H
#define QUADRENDERER3D_H
#include <QVector3D>
#include <QVector2D>
#include <vector>
#include "QuadRendererBase.h"


struct Particle {
    QVector3D	pos;
    QVector3D	speed;
    float		t;
    unsigned short animFrameIndex;
};

typedef std::vector<Particle>   ParticleVec;

struct Quad3D
{
    QVector3D   pos1;
    float       U1, V1;
    QVector3D   pos2;
    float       U2, V2;
    QVector3D   pos3;
    float       U3, V3;
    QVector3D   pos4;
    float       U4, V4;
};


class QuadRenderer3D : public QuadRendererBase
{
public:
    QuadRenderer3D(int maxQuads,  MaterialPtr mat);
    virtual ~QuadRenderer3D();

    Quad3D& getQuad(int idx);
    void    ReserveActiveQuads(int numQuads);
    void    UpdateQuadsBuffer(int numQuads);

private:
    std::vector<Quad3D>  quads;
};

#endif // QUADRENDERER3D_H
