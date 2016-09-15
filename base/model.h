#ifndef MODEL_H
#define	MODEL_H

#include <vector>
#include <assimp/scene.h>       // Output data structure
#include <QOpenGLTexture>
#include "mesh.h"
#include "Entity.h"

class Model : public Entity
{
public:
    Model();
    virtual ~Model();

    bool LoadFile(QString& Filename);

    virtual void	Render(Camera &camera);
    virtual void	Update(float dt);
    virtual bool	IsFinished();

protected:
    int   findMesh(QString name);
    std::vector<Mesh> meshArray;

private:
    void InitFromScene(const aiScene* pScene);
    bool InitMaterials(const aiScene* pScene, QString& folder);
    void Clear();

    QString     getFolder(QString fullpath);

    std::vector<QOpenGLTexture*> textures;
};


#endif	/* MODEL_H */

