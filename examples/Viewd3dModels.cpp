#include "Viewd3dModels.h"

// The first way to render a 3D model is to use the BasicModel() class
// The second way is a more basic manipulation of the Model/Mexh classes

Viewd3DModels::Viewd3DModels()
    : camera(Graphics::phongShader)
    , ground( Graphics::Model.Get(":/models/groundPatch.obj"))
{
    camera.Setup(0.3f, 600.f, 60.f, 1.4f);
    camera.Position = QVector3D(6,2,2);
    camera.LookAt = QVector3D(0,0,0);

    Graphics::phongShader->SetLightPos( QVector3D(5,4,4) );

    monkey = Graphics::Model.Get(":/models/head.obj");
    Begin(360.f);
}

Viewd3DModels::~Viewd3DModels()
{
}

void Viewd3DModels::Render()
{
    if (!Graphics::phongShader->Bind())
        return;

    // 1st method, using the Model class
    float monkeyScale= 1.f + 0.3f*sin(Time*2.f);
    camera.moveModel( QVector3D(0,0,0), QQuaternion::fromAxisAndAngle( 0,1,0, 10*Time), monkeyScale);
    monkey->Render();

    // 2nd method, using the BasicModel class
    ground.Render(&camera);
}

void Viewd3DModels::Update(float dt)
{
    ground.SetPos( QVector3D(0, -1, 0) );
    ground.SetRotation( QQuaternion::fromAxisAndAngle(0,1,0, -Time*20.f) );
}

void Viewd3DModels::Resize(float w, float h)
{

}
