#include "InstanceRenderer.h"

InstanceRenderer::InstanceRenderer(ModelPtr model)
    : _model(model)
{
    meshInstances.resize(model->GetNumMeshes());
}

void InstanceRenderer::AddInstance(int meshIndex, QVector3D pos, QQuaternion rot)
{
    meshInstances[meshIndex].append( Instance(pos,rot) );
}

void InstanceRenderer::Render(CameraPtr cam)
{
    int numMeshes = _model->GetNumMeshes();
    Mesh::EnableGLAttribs();
    for(int i=0; i<numMeshes; ++i)
    {
        RenderArray(cam, _model->GetMesh(i), meshInstances[i]);
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
