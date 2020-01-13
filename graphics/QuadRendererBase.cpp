#include "QuadRendererBase.h"
#include "Ogl.h"

QuadRendererBase::QuadRendererBase()
    : ActiveQuads(0)
    , quadByteSize(0)
    , offset2(0)
    , offset3(0)
    , attrib1Components(0)
    , attrib2Components(0)
    , attrib3Components(0)
    , quadsBuffer(INVALID_OGL_VALUE)
    , indicesBuffer(INVALID_OGL_VALUE)
    , material(nullptr)
{
}

void QuadRendererBase::InitBase(size_t quadByteSize
                                , GLuint ByteOffset2
                                , GLuint ByteOffset3
                                , int glAttrib1Components
                                , int glAttrib2Components
                                , int glAttrib3Components
                                , int maxQuads
                                , MaterialPtr mat)
{
    this->quadByteSize = quadByteSize;
    offset2 = ByteOffset2;
    offset3 = ByteOffset3;
    attrib1Components = glAttrib1Components;
    attrib2Components = glAttrib2Components;
    attrib3Components = glAttrib3Components;

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
    ogl.glVertexAttribPointer(0, attrib1Components, GL_FLOAT, GL_FALSE, quadByteSize/4, 0);  // vertices
    ogl.glVertexAttribPointer(1, attrib2Components, GL_FLOAT, GL_FALSE, quadByteSize/4, (const void*)offset2); // UVs

    if (attrib3Components>0)
    {
        ogl.glEnableVertexAttribArray(2);
        ogl.glVertexAttribPointer(2, attrib3Components, GL_FLOAT, GL_FALSE, quadByteSize/4, (const void*)offset3); // colors/normals
    }

    ogl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    ogl.glDrawElements(GL_TRIANGLES, ActiveQuads*6, GL_UNSIGNED_SHORT, 0);

    ogl.glDisableVertexAttribArray(0);
    ogl.glDisableVertexAttribArray(1);
    ogl.glDisableVertexAttribArray(2);

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
