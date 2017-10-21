#ifndef MESH_H
#define	MESH_H
#include "Vertex.h"
#include "TextureManager.h"

#define INVALID_UNIFORM_LOCATION 0xffffffff
#define INVALID_OGL_VALUE 0xffffffff
#define INVALID_MATERIAL  0xffffffff

#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }

class Mesh {
public:
    Mesh();
    ~Mesh();

    void SetTexture(TexturePtr texture)     { material.SetTexture(texture); }

    static void EnableGLAttribs();
    void Render();

    static void DisableGLAttribs();


    void GenerateBuffers(VertArray &vertices, IndicesArray &indices);

    QString     Name;
    Material    material;

    static int TotalFacesRendered;

protected:
    friend class InstanceRenderer;
    void BeginDrawCall();
    void DrawCall();
    void EndDrawCall();
private:
    GLuint verticesBuffer;
    GLuint indicesBuffer;
    unsigned int NumIndices;
};

#endif
