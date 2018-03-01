#include "QuadRendererBase.h"
#include "Ogl.h"

QuadRendererBase::QuadRendererBase()
    : quadByteSize(0)
    , uvByteOffset(0)
    , numVertexComponents(0)
    , quadsBuffer(INVALID_OGL_VALUE)
    , indicesBuffer(INVALID_OGL_VALUE)
    , ActiveQuads(0)
    , material(0)
{
}

void QuadRendererBase::InitBase(size_t quadByteSize, GLuint uvByteOffset, GLuint colorByteOffset, int numVertexComponents, int maxQuads,  MaterialPtr mat)
{
    this->quadByteSize = quadByteSize;
    this->uvByteOffset = uvByteOffset;
    this->colorByteOffset = colorByteOffset;
    this->numVertexComponents = numVertexComponents;

    material = mat;

    InitIndices(maxQuads);
    ActiveQuads=0;

    ogl.glGenBuffers(1, &quadsBuffer);
    ogl.glBindBuffer(GL_ARRAY_BUFFER, quadsBuffer);
    ogl.glBufferData(GL_ARRAY_BUFFER, quadByteSize * maxQuads, 0, GL_DYNAMIC_DRAW);

    ogl.glGenBuffers(1, &indicesBuffer);
    ogl.glBindBuffer(GL_ARRAY_BUFFER, indicesBuffer);
    ogl.glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned short) * maxQuads*6, &indices[0], GL_STATIC_DRAW);
}


QuadRendererBase::~QuadRendererBase()
{
    if (quadsBuffer != INVALID_OGL_VALUE)
        ogl.glDeleteBuffers(1, &quadsBuffer);
    if (indicesBuffer != INVALID_OGL_VALUE)
        ogl.glDeleteBuffers(1, &indicesBuffer);
}

void QuadRendererBase::InitIndices(int numQuads)
{
    indices.clear();
    indices.reserve(numQuads*6);
    for(int i=0; i<numQuads; ++i)
    {
        int quadBase = i*4;
        indices.push_back( quadBase + 3);
        indices.push_back( quadBase + 0);
        indices.push_back( quadBase + 1);
        indices.push_back( quadBase + 1);
        indices.push_back( quadBase + 2);
        indices.push_back( quadBase + 3);
    }
}

void    QuadRendererBase::ClearQuads()
{
    ActiveQuads = 0;
}

void QuadRendererBase::UpdateQuadsBuffer(const void* quadsData)
{
    ogl.glBindBuffer(GL_ARRAY_BUFFER, quadsBuffer);
    ogl.glBufferData(GL_ARRAY_BUFFER, quadByteSize * ActiveQuads, quadsData, GL_DYNAMIC_DRAW);
}

void	QuadRendererBase::RenderQuads()
{
    if (!!material)
        material->Bind();

    ogl.glEnableVertexAttribArray(0);
    ogl.glEnableVertexAttribArray(1);

    ogl.glBindBuffer(GL_ARRAY_BUFFER, quadsBuffer);
    ogl.glVertexAttribPointer(0, numVertexComponents, GL_FLOAT, GL_FALSE, quadByteSize/4, 0);  // vertices
    ogl.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, quadByteSize/4, (const void*)uvByteOffset); // UVs
    ogl.glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, quadByteSize/4, (const void*)colorByteOffset); // colors

    ogl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    ogl.glDrawElements(GL_TRIANGLES, ActiveQuads*6, GL_UNSIGNED_SHORT, 0);

    ogl.glDisableVertexAttribArray(0);
    ogl.glDisableVertexAttribArray(1);

    if (!!material)
        material->Unbind();
}

MaterialPtr QuadRendererBase::GetMaterial()
{
    return material;
}

void QuadRendererBase::SetMaterial(MaterialPtr mat)
{
    material = mat;
}
