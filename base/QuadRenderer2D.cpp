#include "QuadRenderer2D.h"
#include "Ogl.h"

void Quad2D::SetGeometry(float x, float y, float w, float h)
{
    X1 = X2 = X3 = X4 = x;
    X2 += w;
    X3 += w;

    Y1 = Y2 = Y3 = Y4 = y;
    Y1 += h;
    Y2 += h;
}

void Quad2D::SetUVs(float u1, float v1, float uvWidth, float uvHeight)
{
    U1 = U2 = U3 = U4 = u1;
    U2 += uvWidth;
    U3 += uvWidth;

    V1 = V2 = V3 = V4 = v1;
    V3 += uvHeight;
    V4 += uvHeight;
}

//------------------------------------------------

QuadRenderer2D::QuadRenderer2D()
{
}

QuadRenderer2D::~QuadRenderer2D()
{
}

void QuadRenderer2D::Init(int maxQuads, QString textureFileName)
{
    MaterialPtr mat = new Material(textureFileName);
    QuadRendererBase::Init(sizeof(Quad2D), 8, 2, maxQuads, mat);
    quads.clear();
    quads.reserve(maxQuads);
}

Quad2D& QuadRenderer2D::getQuad(int idx)
{
    return quads[idx];
}

void QuadRenderer2D::UpdateQuadsBuffer()
{
    QuadRendererBase::UpdateQuadsBuffer(&quads[0]);
}

void QuadRenderer2D::ReserveActiveQuads(int numQuads)
{
    ActiveQuads = numQuads;
    quads.resize(numQuads);
}
