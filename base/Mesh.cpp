#include "Mesh.h"
#include "Ogl.h"

Mesh::Mesh()
{
    verticesBuffer = INVALID_OGL_VALUE;
    indicesBuffer = INVALID_OGL_VALUE;
    NumIndices  = 0;
}

Mesh::~Mesh()
{
    if (verticesBuffer != INVALID_OGL_VALUE)
    {
        ogl.glDeleteBuffers(1, &verticesBuffer);
    }

    if (indicesBuffer != INVALID_OGL_VALUE)
    {
        ogl.glDeleteBuffers(1, &indicesBuffer);
    }
}

void Mesh::EnableGLAttribs()
{
    ogl.glEnableVertexAttribArray(0);
    ogl.glEnableVertexAttribArray(1);
    ogl.glEnableVertexAttribArray(2);
}

void Mesh::DisableGLAttribs()
{
    ogl.glDisableVertexAttribArray(0);
    ogl.glDisableVertexAttribArray(1);
    ogl.glDisableVertexAttribArray(2);

}

void Mesh::GenerateBuffers(VertArray& vertices, IndicesArray& indices)
{
    NumIndices = indices.size();

    ogl.glGenBuffers(1, &verticesBuffer);
    ogl.glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    ogl.glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    ogl.glGenBuffers(1, &indicesBuffer);
    ogl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    ogl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * NumIndices, &indices[0], GL_STATIC_DRAW);
}

void Mesh::Render()
{
    material.Bind();
    ogl.glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    ogl.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);  // vertices
    ogl.glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12); // UV's
    ogl.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)20); // Normals

    ogl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    ogl.glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_SHORT, 0);

    material.Unbind();
}
