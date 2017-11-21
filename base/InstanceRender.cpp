#include "InstanceRenderer.h"

InstanceRenderer::InstanceRenderer(ModelPtr _model)
    : model(_model)
{
    meshInstances.resize(_model->GetNumMeshes());
}

//InstanceRenderer::~InstanceRenderer()
//{
//    for(int i=0; i<meshInstances.size(); ++i)
//    {
//        meshInstances[i].clear();
//    }
//    meshInstances.clear();
//}

void InstanceRenderer::AddInstance(int meshIndex, QVector3D pos, QQuaternion rot)
{
    meshInstances[meshIndex].append( Instance(pos,rot) );
}

void InstanceRenderer::Render(CameraPtr cam)
{
    int numMeshes = model->GetNumMeshes();
    Mesh::EnableGLAttribs();
    for(int i=0; i<numMeshes; ++i)
    {
        RenderArray(cam, model->GetMesh(i), meshInstances[i]);
    }
    Mesh::DisableGLAttribs();
}

void InstanceRenderer::RenderArray(CameraPtr cam, Mesh* mesh, InstanceArray &array)
{
    mesh->BeginDrawCall();
    foreach (Instance i, array) {
        cam->moveModel( i.matrix);
        mesh->DrawCall();
    }
    mesh->EndDrawCall();
}
