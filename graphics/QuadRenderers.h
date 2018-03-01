#ifndef _QUADRENDERERS_
#define _QUADRENDERERS_

#include <vector>
#include "QuadTypes.h"
#include "QuadRendererBase.h"
#include "AtlasImporter.h"

#define INVALID_OGL_VALUE 0xffffffff

template<typename QuadType, typename InitSettings>
class Renderer : public QuadRendererBase
{
public:
    Renderer(int maxQuads, MaterialPtr mat)
    {
        InitBase(sizeof(QuadType)
               , InitSettings:: uvByteOffset
               , InitSettings:: colorByteOffset
               , InitSettings:: vertComponents
               , maxQuads, mat);

        quads.clear();
        quads.reserve(maxQuads);
    }

    QuadType& getQuad(int idx)  { return quads[idx]; }

    virtual void UpdateQuadsBuffer()
    {
        QuadRendererBase::UpdateQuadsBuffer(&quads[0]);
    }

    virtual void ReserveActiveQuads(int numQuads)
    {
        ActiveQuads = numQuads;
        quads.resize(numQuads);
    }

private:
    std::vector<QuadType>  quads;
};

typedef Renderer<Quad2D, QuadBufferSettings2D>   QuadRenderer2D;
typedef Renderer<Quad2DX, QuadBufferSettings2DX> QuadRenderer2DX;
typedef Renderer<Quad3D, QuadBufferSettings3D>   QuadRenderer3D;

#endif
