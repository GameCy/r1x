#include "Mesh.h"
#include "Renderer.h"
#include <QFile>
#include <QUrl>
#include "assimphelpers.h"
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

void Mesh::Extract(const aiMesh *paiMesh)
{
    Name = QString( paiMesh->mName.C_Str() );

    QVector<Vertex> Vertices;
    ExtractVertices( paiMesh, Vertices);
    QVector<unsigned short> Indices;
    ExtractIndices( paiMesh, Indices, 0);
    GenerateBuffers(Vertices, Indices);
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

QString Mesh::ExtractTexturePath(const aiScene* pScene, int meshIndex)
{
    int materialIndex = pScene->mMeshes[meshIndex]->mMaterialIndex;
    if (materialIndex>=0 && materialIndex<pScene->mNumMaterials)
    {
        const aiMaterial* pMaterial = pScene->mMaterials[materialIndex];
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString Path;
            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
            {
                return QString().fromStdString(Path.data);
            }
        }
    }
    return QString();
}

void Mesh::ExtractVertices(const aiMesh* paiMesh, QVector<Vertex> &Vertices )
{
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    bool hasUVs = paiMesh->HasTextureCoords(0);
    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
        const aiVector3D* pPos      = &(paiMesh->mVertices[i]);
        const aiVector3D* pTexCoord = hasUVs ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
        const aiVector3D* pNormal   = &(paiMesh->mNormals[i]);

        Vertex v(QVector3D(pPos->x, pPos->y, pPos->z),
                 QVector2D(pTexCoord->x, pTexCoord->y) ,
                 QVector3D(pNormal->x, pNormal->y, pNormal->z) );

        Vertices.push_back(v);
    }
}


void Mesh::ExtractIndices(const aiMesh* paiMesh, QVector<unsigned short> &Indices, int rebase )
{
    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        Indices.push_back(rebase + Face.mIndices[0]);
        Indices.push_back(rebase + Face.mIndices[1]);
        Indices.push_back(rebase + Face.mIndices[2]);
    }
}

void Mesh::GenerateBuffers(QVector<Vertex> &Vertices, QVector<unsigned short> &Indices)
{
    NumIndices = Indices.size();

    ogl.glGenBuffers(1, &verticesBuffer);
    ogl.glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    ogl.glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    ogl.glGenBuffers(1, &indicesBuffer);
    ogl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    ogl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * NumIndices, &Indices[0], GL_STATIC_DRAW);
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
