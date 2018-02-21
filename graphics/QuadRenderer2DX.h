#ifndef QUADRENDERER2DX_H
#define QUADRENDERER2DX_H
#include <QVector3D>
#include <QVector2D>
#include <vector>
#include "QuadRendererBase.h"
#include "AtlasImporter.h"

#define INVALID_OGL_VALUE 0xffffffff

struct Quad2DX
{
    float       X1, Y1, U1, V1, R1,G1,B1,A1;
    float       X2, Y2, U2, V2, R2,G2,B2,A2;
    float       X3, Y3, U3, V3, R3,G3,B3,A3;
    float       X4, Y4, U4, V4, R4,G4,B4,A4;

    void    SetGeometry(float x, float y, float w, float h);
    void    SetUVs(float u1, float v1, float uvWidth, float uvHeight);
    void    SetUVRect(UVRect& uvs);
    void    SetAllColors(QColor color);
};


class QuadRenderer2DX : public QuadRendererBase
{
public:
    QuadRenderer2DX();
    ~QuadRenderer2DX();

    void    Init(int maxQuads, QString textureFileName);
    Quad2DX& getQuad(int idx);
    void    UpdateQuadsBuffer();
    void    ReserveActiveQuads(int numQuads);

private:
    std::vector<Quad2DX>  quads;
};

#endif // QUADRENDERER2DX_H
