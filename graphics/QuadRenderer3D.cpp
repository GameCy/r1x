#include "QuadRenderer3D.h"
#include "Ogl.h"


QuadRenderer3D::QuadRenderer3D(int maxQuads,  MaterialPtr mat)
{
    QuadRendererBase::Init( sizeof(Quad3D), 12, -1, 3, maxQuads, mat);

    quads.clear();
    quads.reserve(maxQuads);
}

QuadRenderer3D::~QuadRenderer3D()
{
}

Quad3D& QuadRenderer3D::getQuad(int idx)
{
    return quads[idx];
}

void QuadRenderer3D::ReserveActiveQuads(int numQuads)
{
    quads.resize(numQuads);
}

void QuadRenderer3D::UpdateQuadsBuffer(int numQuads)
{
    ActiveQuads = numQuads;
    QuadRendererBase::UpdateQuadsBuffer(&quads[0]);
}
