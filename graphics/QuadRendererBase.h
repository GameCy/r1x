#ifndef QUADRENDERERBASE_H
#define QUADRENDERERBASE_H
#include "Material.h"

#define INVALID_OGL_VALUE 0xffffffff

class QuadRendererBase
{
public:
    QuadRendererBase();
    ~QuadRendererBase();

    void    ClearQuads();
    void	RenderQuads();
    MaterialPtr GetMaterial();
    void    SetMaterial(MaterialPtr mat);


protected:
    void    Init(int quadByteSize, int uvByteOffset, int numVertexComponents, int maxQuads, MaterialPtr mat);
    void    UpdateQuadsBuffer(const void* quadsData);
    GLuint  ActiveQuads;

private:
    GLuint  quadByteSize;
    GLuint  uvByteOffset;
    GLuint  numVertexComponents;
    GLuint  quadsBuffer;
    std::vector<unsigned short>  indices;
    GLuint  indicesBuffer;

    MaterialPtr  material;

    void InitIndices(int numQuads);
};

#endif // QUADRENDERERBASE_H
