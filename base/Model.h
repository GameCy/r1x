#ifndef _MODEL_H
#define	_MODEL_H

#include "SmartPtr.h"
#include <QVector>
#include <assimp/scene.h>       // Output data structure
#include "TextureManager.h"
#include "Mesh.h"

class Model : public RefCountBase
{
public:
    Model();
    virtual ~Model();

    bool LoadFile(QString& Filename);

    virtual void	Render();

    Mesh *GetMesh(int meshIndex);
    int     GetNumMeshes();

protected:
    int   findMesh(QString name);
    std::vector<Mesh> meshArray;

private:
    QString Folder;

    void InitFromScene(const aiScene* pScene);
};

typedef SmartPtr<Model>     ModelPtr;

#endif
