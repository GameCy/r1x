#include "QuadRenderer2DX.h"
#include "Ogl.h"

void Quad2DX::SetGeometry(float x, float y, float w, float h)
{
    X1 = X2 = X3 = X4 = x;
    X2 += w;
    X3 += w;

    Y1 = Y2 = Y3 = Y4 = y;
    Y1 += h;
    Y2 += h;
}

void Quad2DX::SetUVs(float u1, float v1, float uvWidth, float uvHeight)
{
    U1 = U2 = U3 = U4 = u1;
    U2 += uvWidth;
    U3 += uvWidth;

    V1 = V2 = V3 = V4 = v1;
    V3 += uvHeight;
    V4 += uvHeight;
}

void Quad2DX::SetUVRect(UVRect &uvs)
{
    U1 = uvs.U1;    V1 = uvs.V1;
    U2 = uvs.U2;    V2 = uvs.V1;
    U3 = uvs.U2;    V3 = uvs.V2;
    U4 = uvs.U1;    V4 = uvs.V2;
}

void Quad2DX::SetAllColors(QColor color)
{
    R1=R2=R3=color.redF();
    G1=G2=G3=color.greenF();
    B1=B2=B3=color.blueF();
    A1=A2=A3=color.alphaF();
}

//------------------------------------------------

QuadRenderer2DX::QuadRenderer2DX()
{
}

QuadRenderer2DX::~QuadRenderer2DX()
{
}

void QuadRenderer2DX::Init(int maxQuads, QString textureFileName)
{
    MaterialPtr mat = new Material(textureFileName);
    QuadRendererBase::Init(sizeof(Quad2DX), 8, 16, 2, maxQuads, mat);
    quads.clear();
    quads.reserve(maxQuads);
}

Quad2DX& QuadRenderer2DX::getQuad(int idx)
{
    return quads[idx];
}

void QuadRenderer2DX::UpdateQuadsBuffer()
{
    QuadRendererBase::UpdateQuadsBuffer(&quads[0]);
}

void QuadRenderer2DX::ReserveActiveQuads(int numQuads)
{
    ActiveQuads = numQuads;
    quads.resize(numQuads);
}
