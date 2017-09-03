#include "Model.h"
#include "Assets.h"
#include "Utils.h"
#include "OBJLoader.h"

Model::Model()
{
}

Model::~Model()
{
}

bool Model::LoadFile(QString& filePath)
{
    Folder = Utils::getFolder(filePath);

    OBJLoader::Loader loader;
    if (loader.LoadFile(filePath))
    {
        InitFromLoader(loader);
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

Mesh* Model::GetMesh(size_t meshIndex)
{
    if (meshIndex>=meshArray.size() || meshIndex<0)
        return 0;
    return &meshArray[meshIndex];
}

Mesh* Model::GetMesh(QString name)
{
    int idx = findMesh(name);
    if (idx<0)
        return 0;
    return &meshArray[idx];
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

void Model::InitFromLoader(OBJLoader::Loader &loader)
{
    size_t numMeshes = loader.LoadedMeshes.size();
    meshArray.resize(numMeshes);

    for (size_t i = 0 ; i < numMeshes ; i++)
    {
        OBJLoader::Mesh &mesh = loader.LoadedMeshes[i];

        QString texPath = Folder + "/" + Utils::getFile( mesh.material.map_Kd );
        TexturePtr texture = Assets::Texture.Get(texPath);
        meshArray[i].material.SetTexture( texture );
        meshArray[i].GenerateBuffers(mesh.Vertices, mesh.Indices);
        meshArray[i].Name = mesh.MeshName;
    }
}
