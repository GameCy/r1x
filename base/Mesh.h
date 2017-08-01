/*

	Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MESH_H
#define	MESH_H

#include <QVector3D>
#include <QVector2D>
#include <assimp/scene.h>       // Output data structure
#include <QOpenGLTexture>
#include "Entity.h"

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

    void InitFromAssimp(const aiMesh* paiMesh, QOpenGLTexture* texture);

    void Render();

    static void EnableGLAttribs();
    static void DisableGLAttribs();

    QString Name;

private:
    GLuint verticesBuffer;
    GLuint indicesBuffer;
    unsigned int NumIndices;
    QOpenGLTexture* Texture;
};

#endif	/* MESH_H */

