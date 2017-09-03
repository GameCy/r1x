#ifndef _MODEL_H
#define	_MODEL_H

#include "SmartPtr.h"
#include <QVector>
#include "TextureManager.h"
#include "Mesh.h"

namespace  OBJLoader {class Loader; }

class Model : public RefCountBase
{
public:
    Model();
    virtual ~Model();

    bool LoadFile(QString& filePath);

    virtual void	Render();

    Mesh *GetMesh(size_t meshIndex);
    Mesh* GetMesh(QString name);

    int     GetNumMeshes();

protected:
    int   findMesh(QString name);
    std::vector<Mesh> meshArray;

private:
    QString Folder;

    void InitFromLoader(OBJLoader::Loader &loader);
};

typedef SmartPtr<Model>     ModelPtr;

#endif
