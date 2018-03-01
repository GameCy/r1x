#ifndef QUADRENDERERBASE_H
#define QUADRENDERERBASE_H
#include "Material.h"

#define INVALID_OGL_VALUE 0xffffffff

class QuadRendererBase
{
public:
    QuadRendererBase();
    ~QuadRendererBase();

    virtual void ReserveActiveQuads(int numQuads)=0;
    virtual void UpdateQuadsBuffer()=0;

    void    ClearQuads();
    void	RenderQuads();

    MaterialPtr GetMaterial();
    void    SetMaterial(MaterialPtr mat);

protected:
    void    InitBase(size_t quadByteSize, GLuint uvByteOffset, GLuint colorByteOffset
                 , int numVertexComponents, int maxQuads, MaterialPtr mat);
    void    UpdateQuadsBuffer(const void* quadsData);
    GLuint  ActiveQuads;

private:
    GLuint  quadByteSize;
    GLuint  uvByteOffset;
    GLuint  colorByteOffset;
    GLuint  numVertexComponents;
    GLuint  quadsBuffer;
    std::vector<unsigned short>  indices;
    GLuint  indicesBuffer;

    MaterialPtr  material;

    void InitIndices(int numQuads);
};

#endif // QUADRENDERERBASE_H
