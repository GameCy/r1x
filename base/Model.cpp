#include "Model.h"
#include <QFile>
#include <QUrl>
#include "assimphelpers.h"
#include "Ogl.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h> // Post processing flags
#include "Assets.h"
#include "Utils.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::LoadFile(QString& Filename)
{
    Folder = Utils::getFolder(Filename);

    Assimp::Importer Importer;
    Importer.SetIOHandler(new Qt3D::AssimpHelper::AssimpIOSystem());
    const aiScene* pScene = Importer.ReadFile(Filename.toStdString().c_str()
                                    , aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
    
    if (pScene)
    {
        InitFromScene(pScene);
        //delete pScene;
        return true;
    }

    return false;
}

void Model::Render()
{
    Mesh::EnableGLAttribs();

    for (unsigned int i = 0 ; i < meshArray.size() ; i++)
        meshArray[i].Render();

    Mesh::DisableGLAttribs();
}

Mesh* Model::GetMesh(int meshIndex)
{
    if (meshIndex>=meshArray.size() || meshIndex<0)
        return 0;
    return &meshArray[meshIndex];
}

int Model::GetNumMeshes()
{
    return meshArray.size();
}

int   Model::findMesh(QString name)
{
    for (unsigned int i = 0 ; i < meshArray.size() ; i++)
    {
        if (name.compare(meshArray[i].Name)==0)
            return i;
    }
    return -1;
}

void Model::InitFromScene(const aiScene* pScene)
{
    meshArray.resize(pScene->mNumMeshes);

    for (unsigned int i = 0 ; i < meshArray.size() ; i++)
    {
        QString texPath = Folder + "/" + Mesh::ExtractTexturePath(pScene, i);
        meshArray[i].material.SetTexture( Assets::Texture.Get(texPath) );
        meshArray[i].Extract( pScene->mMeshes[i]);
    }
}

