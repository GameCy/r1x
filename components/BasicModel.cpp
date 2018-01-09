#include "BasicModel.h"

BasicModel::BasicModel(ModelPtr model)
    : Hidden(false)
{
    this->model = model;
}

void BasicModel::Render(CameraPtr camera)
{
    if (Hidden || (!model))
        return;

    camera->moveModel( GetPos(), GetRotation() );
    Mesh::EnableGLAttribs();
        model->Render();
    Mesh::DisableGLAttribs();
}

void BasicModel::Update(float dt)
{

}

bool BasicModel::IsFinished()
{
    return false;
}
