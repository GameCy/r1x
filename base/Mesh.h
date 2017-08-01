#ifndef MESH_H
#define	MESH_H

#include <QVector3D>
#include <QVector2D>
#include <assimp/scene.h>       // Output data structure
#include "TextureManager.h"

#define INVALID_UNIFORM_LOCATION 0xffffffff
#define INVALID_OGL_VALUE 0xffffffff
#define INVALID_MATERIAL  0xffffffff

#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

struct Vertex
{
    QVector3D m_pos;
    QVector2D m_tex;
    QVector3D m_normal;

    Vertex() {}

    Vertex( const QVector3D& pos, const QVector2D& tex, const QVector3D& normal)
    {
        m_pos    = pos;
        m_tex    = tex;
        m_normal = normal;
    }
};

// -----------

class Mesh {
public:
    Mesh();
    ~Mesh();

    void Extract(const aiMesh* paiMesh);
    void SetTexture(TexturePtr texture)     { material.SetTexture(texture); }

    void Render();

    static void EnableGLAttribs();
    static void DisableGLAttribs();
    static QString ExtractTexturePath(const aiScene* pScene, int meshIndex);

    QString     Name;
    Material    material;

private:
    GLuint verticesBuffer;
    GLuint indicesBuffer;
    unsigned int NumIndices;

    void ExtractVertices(const aiMesh* paiMesh, QVector<Vertex> &Vertices);
    void ExtractIndices(const aiMesh* paiMesh, QVector<unsigned short> &Indices, int rebase);
    void GenerateBuffers(QVector<Vertex> &Vertices, QVector<unsigned short> &Indices);
};

#endif
