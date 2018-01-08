#ifndef QUADRENDERER2D_H
#define QUADRENDERER2D_H
#include <QVector3D>
#include <QVector2D>
#include <vector>
#include "QuadRendererBase.h"
#include "AtlasImporter.h"

#define INVALID_OGL_VALUE 0xffffffff

struct Quad2D
{
    float       X1, Y1, U1, V1;
    float       X2, Y2, U2, V2;
    float       X3, Y3, U3, V3;
    float       X4, Y4, U4, V4;

    void    SetGeometry(float x, float y, float w, float h);
    void    SetUVs(float u1, float v1, float uvWidth, float uvHeight);
    void    SetUVRect(UVRect& uvs);
};


class QuadRenderer2D : public QuadRendererBase
{
public:
    QuadRenderer2D();
    ~QuadRenderer2D();

    void    Init(int maxQuads, QString textureFileName);
    Quad2D& getQuad(int idx);
    void    UpdateQuadsBuffer();
    void    ReserveActiveQuads(int numQuads);

private:
    std::vector<Quad2D>  quads;
};

#endif // QUADRENDERER2D_H
