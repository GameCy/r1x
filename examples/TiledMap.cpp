#include "TiledMap.h"


TiledMap::TiledMap()
    : camera(Graphics::phongShader)
{
    camera.Setup(0.3f, 600.f, 60.f, 1.4f);
    camera.Position = QVector3D(6,2,2);
    camera.LookAt = QVector3D(0,0,0);

    tmxparser::parseTmxFromJSON_file(":/tiledMaps/testLevel.json", &tmxMap);

    Begin(360.f);
}

TiledMap::~TiledMap()
{
}

void TiledMap::Render()
{
    if (!Graphics::rasterShader->Bind())
        return;

    // 1st method, using the Model class
    float monkeyScale= 1.f + 0.3f*sin(Time*2.f);
    camera.moveModel( QVector3D(0,0,0), QQuaternion::fromAxisAndAngle( 0,1,0, 10*Time), monkeyScale);
    //monkey->Render();

}

void TiledMap::Update(float dt)
{
}

void TiledMap::Resize(ViewPort &screen)
{
}
