#include "Viewd3dModels.h"

// The first way to render a 3D model is to use the BasicModel() class
// The second way is a more basic manipulation of the Model/Mexh classes

Viewd3DModels::Viewd3DModels()
    : camera(Graphics::phongShader)
    , angle(0)
    , ground( Graphics::Model.Get(":/models/groundPatch.obj"))
{
    camera.Setup(0.3f, 600.f, 60.f, 1.4f);
    monkey = Graphics::Model.Get(":/models/head.obj");
}

void Viewd3DModels::Render()
{
    Graphics::phongShader->SetLightPos( QVector3D(5,4,4) );
    Graphics::phongShader->ParticleRenderingMode(false);

    camera.Position = QVector3D(6,2,2);
    camera.LookAt = QVector3D(0,0,0);

    // 1st method, using the Model class
    QMatrix4x4 matrix;
    matrix.rotate( angle, 0.f, 1.f, 0.f);
    camera.moveModel(matrix);
    monkey->Render();

    // 2nd method, using the BasicModel class
    ground.SetPos( QVector3D(0, -1, 0) );
    ground.SetRotation( QQuaternion::fromAxisAndAngle(0,1,0, -angle/3.f) );
    ground.Render(&camera);
}

void Viewd3DModels::Update(float dt)
{
    angle += dt*60.f;
}

void Viewd3DModels::Resize(float w, float h)
{

}
