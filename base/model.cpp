#include "model.h"
#include "EntityManager.h"
#include <QFile>
#include <QUrl>
#include "assimphelpers.h"
#include "ogl.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h> // Post processing flags


Model::Model()
{
}

Model::~Model()
{
    Clear();
}


void Model::Clear()
{
    for (unsigned int i = 0 ; i < textures.size() ; i++) {
        SAFE_DELETE(textures[i]);
    }
}

bool Model::LoadFile(QString& Filename)
{
    Clear(); // Release any previously loaded mesh
    
    bool Ret = false;
    Assimp::Importer Importer;

    Importer.SetIOHandler(new Qt3D::AssimpHelper::AssimpIOSystem());

    const aiScene* pScene = Importer.ReadFile(Filename.toStdString().c_str()
                                    , aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
    
    if (pScene)
    {
        QString folder = getFolder(Filename);
        InitMaterials(pScene, folder);
        InitFromScene(pScene);
    }
    //else    printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());

    return Ret;
}

void Model::InitFromScene(const aiScene* pScene)
{
    meshArray.resize(pScene->mNumMeshes);

    for (unsigned int i = 0 ; i < meshArray.size() ; i++)
    {
        QOpenGLTexture* tex = 0;
        int idx = pScene->mMeshes[i]->mMaterialIndex;
        if (idx>=0 && idx< textures.size())
            tex = textures[idx];

        meshArray[i].InitFromAssimp( pScene->mMeshes[i], tex );
    }
}


QString Model::getFolder(QString fullpath)
{
    int SlashIndex = fullpath.lastIndexOf("/");

    if (SlashIndex <0)          return ".";
    else if (SlashIndex == 0)   return "/";
    else                        return fullpath.mid(0, SlashIndex);
}


bool Model::InitMaterials(const aiScene* pScene, QString& folder)
{
    bool Ret = true;
    textures.resize(pScene->mNumMaterials);

    // Initialize the materials
    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                QString FullPath = folder+"/"+ QString().fromStdString(Path.data);
                QImage image;
                if (image.load( FullPath))
                {
                    printf("Loaded texture '%s'\n", FullPath.toStdString().c_str());
                    textures[i] = new QOpenGLTexture(image);
                }
                else
                {
                    printf("Error loading texture '%s'\n", FullPath.toStdString().c_str());
                    Ret = false;
                }
            }
        }

        // Load a white texture in case the model does not include its own texture
        if (!textures[i]) {
            textures[i] = new QOpenGLTexture( QImage("../Content/white.png"));
        }
    }

    return Ret;
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

void Model::Render(Camera &camera)
{
    camera.moveModel( GetPos(), GetRotation() );

    Mesh::EnableGLAttribs();

    for (unsigned int i = 0 ; i < meshArray.size() ; i++)
        meshArray[i].Render();

    Mesh::DisableGLAttribs();
}

void	Model::Update(float dt)
{

}

bool	Model::IsFinished()
{
    return false;
}
