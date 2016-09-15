#include "QuadRenderer.h"
//#include "EntityManager.h"
#include "ogl.h"


QuadRenderer::QuadRenderer(int maxQuads,  TextureAnimPtr texAnim)
    : quadsBuffer(INVALID_OGL_VALUE), indicesBuffer(INVALID_OGL_VALUE), ActiveQuads(0)
{
    textureAnim = texAnim;
    quads.clear();
    quads.reserve(maxQuads);
    InitIndices(maxQuads);
    ActiveQuads=0;

    ogl.glGenBuffers(1, &quadsBuffer);
    ogl.glBindBuffer(GL_ARRAY_BUFFER, quadsBuffer);
    ogl.glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleQuad) * maxQuads, &quads[0], GL_DYNAMIC_DRAW);

    ogl.glGenBuffers(1, &indicesBuffer);
    ogl.glBindBuffer(GL_ARRAY_BUFFER, indicesBuffer);
    ogl.glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned short) * maxQuads*6, &indices[0], GL_STATIC_DRAW);
}

QuadRenderer::~QuadRenderer()
{
    if (quadsBuffer != INVALID_OGL_VALUE)
        ogl.glDeleteBuffers(1, &quadsBuffer);
    if (indicesBuffer != INVALID_OGL_VALUE)
        ogl.glDeleteBuffers(1, &indicesBuffer);
}

void QuadRenderer::InitIndices(int numQuads)
{
    indices.clear();
    indices.reserve(numQuads*6);
    for(int i=0; i<numQuads; ++i)
    {
        indices.push_back( i*4 + 3);
        indices.push_back( i*4 + 0);
        indices.push_back( i*4 + 1);
        indices.push_back( i*4 + 1);
        indices.push_back( i*4 + 2);
        indices.push_back( i*4 + 3);
    }
}

void    QuadRenderer::ClearQuads()
{
    ActiveQuads = 0;
}

ParticleQuad& QuadRenderer::getQuad(int idx)
{
    return quads[idx];
}

void QuadRenderer::reserveActiveQuads(int numQuads)
{
    ActiveQuads = numQuads;
    quads.resize(numQuads);
}

void	QuadRenderer::RenderQuads()
{
    ogl.glDepthMask(0);
    ogl.glEnable(GL_BLEND);
    ogl.glBlendFunc(GL_BLEND_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!!textureAnim)
        textureAnim->material.texture->bind(); // this should be inside Material class

    ogl.glEnableVertexAttribArray(0);
    ogl.glEnableVertexAttribArray(1);

    ogl.glBindBuffer(GL_ARRAY_BUFFER, quadsBuffer);
    ogl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ParticleQuad)/4, 0);  // vertices
    ogl.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ParticleQuad)/4, (const void*)12); // UV's

    ogl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    ogl.glDrawElements(GL_TRIANGLES, ActiveQuads*6, GL_UNSIGNED_SHORT, 0);

    ogl.glDisableVertexAttribArray(0);
    ogl.glDisableVertexAttribArray(1);

    ogl.glDisable(GL_BLEND);
    ogl.glDepthMask(1);
}

void QuadRenderer::UpdateQuadsBuffer()
{
    ogl.glBindBuffer(GL_ARRAY_BUFFER, quadsBuffer);
    ogl.glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleQuad) * ActiveQuads, &quads[0], GL_DYNAMIC_DRAW);
}



